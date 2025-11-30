#include "CreditsRepository.h"

CreditsRepository::CreditsRepository()
    : _db(AppContext::get<Database>())
{}

CreditsResponse CreditsRepository::findByAccount(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select
                c.id, c.account_id, c.product_id, cp.name as product_name, c.amount,
                c.interest_accrued, c.remaining_amount,
                to_char(c.opened_at, 'YYYY-MM-DD"T"HH24:MI:SSZ') as opened_at,
                coalesce(to_char(c.closed_at, 'YYYY-MM-DD"T"HH24:MI:SSZ'), '') as closed_at
            from credits c
            join credit_products cp on cp.id = c.product_id
            where c.account_id = $1 and c.closed_at is null
            order by c.opened_at desc
        )SQL",
        pqxx::params(accountId)
    );

    CreditsResponse res;
    for (const auto& row : result) {
        res.credits.push_back({
            row["id"].as<int>(),
            row["account_id"].as<int>(),
            row["product_id"].as<int>(),
            row["product_name"].as<string>(),
            row["amount"].as<double>(),
            row["interest_accrued"].as<double>(),
            row["remaining_amount"].as<double>(),
            row["opened_at"].as<string>(),
            row["closed_at"].as<string>()
        });
    }
    return res;
}

optional<CreditResponse> CreditsRepository::findById(int accountId, int creditId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select
                c.id, c.account_id, c.product_id, cp.name as product_name, c.amount,
                c.interest_accrued, c.remaining_amount,
                to_char(c.opened_at, 'YYYY-MM-DD"T"HH24:MI:SSZ') as opened_at,
                coalesce(to_char(c.closed_at, 'YYYY-MM-DD"T"HH24:MI:SSZ'), '') as closed_at
            from credits c
            join credit_products cp on cp.id = c.product_id
            where c.id = $1 and c.account_id = $2
            limit 1
        )SQL",
        pqxx::params(creditId, accountId)
    );

    if (result.empty()) return nullopt;

    const auto& row = result[0];
    CreditResponse credit{
        row["id"].as<int>(),
        row["account_id"].as<int>(),
        row["product_id"].as<int>(),
        row["product_name"].as<string>(),
        row["amount"].as<double>(),
        row["interest_accrued"].as<double>(),
        row["remaining_amount"].as<double>(),
        row["opened_at"].as<string>(),
        row["closed_at"].as<string>()
    };
    return credit;
}
