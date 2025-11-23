create table clients (
    id serial primary key,
    full_name varchar(100) not null check (char_length(full_name) > 0)
);

create table accounts (
    id serial primary key,
    client_id int not null references clients(id),
    balance numeric(18,2) not null default 0 check (balance >= 0)
);

create table cards (
    id serial primary key,
    account_id int not null unique references accounts(id),
    card varchar(16) not null unique check (char_length(card) = 16),
    pin varchar(4) not null check (pin ~ '^[0-9]{4}$'),
    cvv varchar(3) not null check (cvv ~ '^[0-9]{3}$'),
    expiration_date date not null
);

create table deposit_products (
    id serial primary key,
    name varchar(100) not null unique,
    term_months int not null check (term_months > 0),
    interest_rate numeric(5,2) not null check (interest_rate > 0),
    unique(term_months, interest_rate)
);

create table credit_products (
    id serial primary key,
    name varchar(100) not null unique,
    term_months int not null check (term_months > 0),
    interest_rate numeric(5,2) not null check (interest_rate > 0),
    unique(term_months, interest_rate)
);

create table deposits (
    id serial primary key,
    account_id int not null references accounts(id),
    product_id int not null references deposit_products(id),
    amount numeric(18,2) not null check (amount > 0),
    opened_at timestamptz not null default now(),
    closed_at timestamptz
);

create table credits (
    id serial primary key,
    account_id int not null references accounts(id),
    product_id int not null references credit_products(id),
    amount numeric(18,2) not null check (amount > 0),
    opened_at timestamptz not null default now(),
    closed_at timestamptz,
    interest_accrued numeric(18,2) not null default 0,
    remaining_amount numeric(18,2) not null,
    last_interest_calc timestamptz not null default now()
);

create table credit_payments (
    id serial primary key,
    credit_id int not null references credits(id),
    amount numeric(18,2) not null check (amount > 0),
    paid_at timestamptz not null default now()
);

create type operation_type_enum as enum (
    'transfer',
    'deposit_open',
    'deposit_close',
    'atm_withdraw',
    'atm_deposit',
    'daemon_adjustment',
    'credit_issue',
    'credit_payment',
    'credit_close'
);

create type entity_type_enum as enum (
    'deposit',
    'credit',
    'atm'
);

create table operations (
    id serial primary key,
    src_account_id int references accounts(id),
    trg_account_id int references accounts(id),
    entity_type entity_type_enum,
    entity_id int,
    amount numeric(18,2) not null check (amount > 0),
    type operation_type_enum not null,
    created_at timestamptz not null default now()
);

create or replace function process_operation()
returns trigger as $$
declare
    v_deposit_id int;
    v_rate numeric;
    v_term int;
    v_opened timestamptz;
    v_interest numeric;
begin
    if new.type = 'transfer' then
        update accounts set balance = balance - new.amount where id = new.src_account_id;
        update accounts set balance = balance + new.amount where id = new.trg_account_id;

    elsif new.type = 'atm_withdraw' then
        update accounts set balance = balance - new.amount where id = new.src_account_id;

    elsif new.type = 'atm_deposit' then
        update accounts set balance = balance + new.amount where id = new.trg_account_id;

    elsif new.type = 'deposit_open' then
        insert into deposits(account_id, product_id, amount)
        values (new.src_account_id, new.entity_id, new.amount);

        update accounts
        set balance = balance - new.amount
        where id = new.src_account_id;

    elsif new.type = 'deposit_close' then
        select id, d.amount, dp.interest_rate, dp.term_months, d.opened_at
        into v_deposit_id, new.amount, v_rate, v_term, v_opened
        from deposits d
        join deposit_products dp on dp.id = d.product_id
        where d.id = new.entity_id
          and d.account_id = new.src_account_id
          and d.closed_at is null;

        if not found then
            raise exception 'deposit not found';
        end if;

        v_interest := 0;
        if now() >= v_opened + (v_term || ' month')::interval then
            v_interest := new.amount * (v_rate / 100) * (v_term / 12.0);
        end if;

        update deposits
        set closed_at = now()
        where id = v_deposit_id;

        update accounts
        set balance = balance + new.amount + v_interest
        where id = new.src_account_id;

    elsif new.type = 'credit_issue' then
        insert into credits(account_id, product_id, amount, remaining_amount)
        values (new.trg_account_id, new.entity_id, new.amount, new.amount);

        update accounts
        set balance = balance + new.amount
        where id = new.trg_account_id;

    elsif new.type = 'credit_payment' then
        update accounts
        set balance = balance - new.amount
        where id = new.src_account_id;

        insert into credit_payments(credit_id, amount)
        values (new.entity_id, new.amount);

        update credits
        set remaining_amount = remaining_amount - new.amount
        where id = new.entity_id;

        update credits
        set closed_at = now()
        where id = new.entity_id
          and remaining_amount <= 0
          and closed_at is null;

    elsif new.type = 'credit_close' then
        update credits
        set closed_at = now()
        where id = new.entity_id;

    end if;

    return new;
end;
$$ language plpgsql;

drop trigger if exists trigger_process_operation on operations;
create trigger trigger_process_operation
after insert on operations
for each row
execute procedure process_operation();

create extension if not exists pg_cron;

create or replace function credit_interest_daemon()
returns void as $$
declare
    r record;
    v_daily numeric;
begin
    for r in
        select c.id, c.remaining_amount, c.interest_accrued,
               c.last_interest_calc, cp.interest_rate
        from credits c
        join credit_products cp on cp.id = c.product_id
        where c.closed_at is null
    loop
        if now()::date > r.last_interest_calc::date then
            v_daily := r.remaining_amount * (r.interest_rate / 100) / 365;

            update credits
            set interest_accrued = interest_accrued + v_daily,
                remaining_amount = remaining_amount + v_daily,
                last_interest_calc = now()
            where id = r.id;
        end if;
    end loop;
end;
$$ language plpgsql;

select cron.schedule(
    'credit_interest_daily',
    '10 0 * * *',
    $$select credit_interest_daemon();$$
);

create type periodicity_enum as enum ('once', 'weekly', 'monthly', 'yearly');

create table auto_transfers (
    id serial primary key,
    src_account_id int not null references accounts(id) on delete cascade,
    trg_account_id int not null references accounts(id),
    amount numeric(18,2) check (amount > 0),
    periodicity periodicity_enum not null,
    next_run_date date not null,
    active boolean not null default true
);

create table leftover_rules (
    id serial primary key,
    src_account_id int not null references accounts(id) on delete cascade,
    trg_account_id int not null references accounts(id),
    threshold numeric(18,2) not null check (threshold > 0),
    active boolean not null default true
);

create table credit_protection_rules (
    id serial primary key,
    protected_account_id int not null references accounts(id) on delete cascade,
    backup_account_id int not null references accounts(id),
    min_balance numeric(18,2) not null check (min_balance >= 0),
    active boolean not null default true
);

create or replace function run_auto_transfers(p_today date default now()::date)
returns void as $$
declare
    r record;
    v_balance numeric(18,2);
begin
    for r in
        select *
        from auto_transfers
        where active = true
          and next_run_date <= p_today
    loop
        select balance into v_balance
        from accounts
        where id = r.src_account_id;

        if v_balance < r.amount then
            continue;
        end if;

        insert into operations(src_account_id, trg_account_id, entity_type, entity_id, amount, type)
        values (r.src_account_id, r.trg_account_id, null, null, r.amount, 'transfer');

        if r.periodicity = 'once' then
            update auto_transfers set active = false where id = r.id;
        elsif r.periodicity = 'weekly' then
            update auto_transfers set next_run_date = r.next_run_date + interval '1 week' where id = r.id;
        elsif r.periodicity = 'monthly' then
            update auto_transfers set next_run_date = r.next_run_date + interval '1 month' where id = r.id;
        elsif r.periodicity = 'yearly' then
            update auto_transfers set next_run_date = r.next_run_date + interval '1 year' where id = r.id;
        end if;
    end loop;
end;
$$ language plpgsql;

create or replace function run_leftover_daemon()
returns void as $$
declare
    r record;
    v_balance numeric(18,2);
    v_extra numeric(18,2);
begin
    for r in
        select *
        from leftover_rules
        where active = true
    loop
        select balance into v_balance
        from accounts
        where id = r.src_account_id;

        if v_balance > r.threshold then
            v_extra := v_balance - r.threshold;

            insert into operations(src_account_id, trg_account_id, entity_type, entity_id, amount, type)
            values (r.src_account_id, r.trg_account_id, null, null, v_extra, 'transfer');
        end if;
    end loop;
end;
$$ language plpgsql;

create or replace function run_credit_protection_daemon()
returns void as $$
declare
    r record;
    v_balance_protected numeric(18,2);
    v_balance_backup numeric(18,2);
    v_needed numeric(18,2);
    v_amount numeric(18,2);
begin
    for r in
        select *
        from credit_protection_rules
        where active = true
    loop
        select balance into v_balance_protected
        from accounts
        where id = r.protected_account_id;

        if v_balance_protected >= r.min_balance then
            continue;
        end if;

        v_needed := r.min_balance - v_balance_protected;

        select balance into v_balance_backup
        from accounts
        where id = r.backup_account_id;

        if v_balance_backup <= 0 then
            continue;
        end if;

        v_amount := least(v_needed, v_balance_backup);

        if v_amount <= 0 then
            continue;
        end if;

        insert into operations(src_account_id, trg_account_id, entity_type, entity_id, amount, type)
        values (r.backup_account_id, r.protected_account_id, null, null, v_amount, 'transfer');
    end loop;
end;
$$ language plpgsql;

select cron.schedule(
    'leftover_daily',
    '0 2 * * *',
    $$select run_leftover_daemon();$$
);

select cron.schedule(
    'auto_transfers_daily',
    '0 1 * * *',
    $$select run_auto_transfers();$$
);

select cron.schedule(
    'credit_protection_daily',
    '0 3 * * *',
    $$select run_credit_protection_daemon();$$
);


create index idx_accounts_client_id on accounts(client_id);
create index idx_operations_src_account on operations(src_account_id);
create index idx_operations_trg_account on operations(trg_account_id);
create index idx_operations_type on operations(type);
create index idx_deposits_account_id on deposits(account_id);
create index idx_credits_account_id on credits(account_id);
create index idx_auto_transfers_src on auto_transfers(src_account_id);
create index idx_leftover_rules_src on leftover_rules(src_account_id);
create index idx_credit_protection_protected on credit_protection_rules(protected_account_id);


insert into clients(full_name) 
values
	('Alexandr Stepanov'), 
	('Cameron Hall');
insert into accounts(client_id, balance) 
values 
	(1, 0), 
	(2, 0);

insert into cards(account_id, client_id, card, pin, cvv, expiration_date)
values
	(1, 1, '4556301788579802', '1234', '911', '2027-02-01'),
	(2, 2, '4556727619519847', '9347', '437', '2032-09-01');

insert into deposit_products (name, term_months, interest_rate)
values 
	('standard 3M', 3, 5),
	('premium 6M', 6, 7.5),
	('gold 12M', 12, 10);

insert into credit_products(name, term_months, interest_rate)
values 
	('standard 6M', 6, 15),
    ('premium 12M', 12, 12),
    ('gold 24M', 24, 9);
