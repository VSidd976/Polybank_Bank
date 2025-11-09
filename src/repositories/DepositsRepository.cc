#include "DepositsRepository.h"

DepositsRepository::DepositsRepository()
    : _db(AppContext::get<Database>())
{}

DepositsResponse DepositsRepository::findByAccount(int account_id) {
    pqxx::work tx(_db.getConn());
    auto result = tx.exec(
        R"SQL(
            select
                id, account_id, product_id, amount,
                to_char(opened_at, 'YYYY-MM-DD"T"HH24:MI:SSZ') as opened_at,
                coalesce(to_char(closed_at, 'YYYY-MM-DD"T"HH24:MI:SSZ'), '') as closed_at
            from deposits
            where account_id = $1
            order by opened_at desc
        )SQL",
        pqxx::params(account_id)
    );

    DepositsResponse res;
    for (const auto& row : result) {
        res._deposits.push_back({
            row["id"].as<int>(),
            row["account_id"].as<int>(),
            row["product_id"].as<int>(),
            row["amount"].as<double>(),
            row["opened_at"].as<string>(),
            row["closed_at"].as<string>()
        });
    }

    return res;
}

optional<DepositResponse> DepositsRepository::findById(int account_id, int deposit_id) {
    pqxx::work tx(_db.getConn());
    auto result = tx.exec(
        R"SQL(
            select
                id, account_id, product_id, amount,
                to_char(opened_at, 'YYYY-MM-DD"T"HH24:MI:SSZ') as opened_at,
                coalesce(to_char(closed_at, 'YYYY-MM-DD"T"HH24:MI:SSZ'), '') as closed_at
            from deposits
            where id = $1 and account_id = $2
            limit 1
        )SQL",
        pqxx::params(deposit_id, account_id)
    );

    if (result.empty())
        return nullopt;

    const auto& row = result[0];
    DepositResponse deposit{
        row["id"].as<int>(),
        row["account_id"].as<int>(),
        row["product_id"].as<int>(),
        row["amount"].as<double>(),
        row["opened_at"].as<string>(),
        row["closed_at"].as<string>()
    };

    return deposit;
}

bool DepositsRepository::openDeposit(int account_id, int product_id, double amount) {
    try {
        pqxx::work tx(_db.getConn());
        tx.exec(
            R"SQL(
                insert into operations(from_account_id, to_account_id, amount, type)
                values ($1, $2, $3, 'deposit_open')
            )SQL",
            pqxx::params(account_id, product_id, amount)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}

bool DepositsRepository::closeDeposit(int account_id, int deposit_id) {
    try {
        pqxx::work tx(_db.getConn());
        tx.exec(
            R"SQL(
                insert into operations(from_account_id, to_account_id, amount, type)
                select $1, $2, amount, 'deposit_close'
                from deposits
                where id = $2 and account_id = $1 and closed_at is null
            )SQL",
            pqxx::params(account_id, deposit_id)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}
