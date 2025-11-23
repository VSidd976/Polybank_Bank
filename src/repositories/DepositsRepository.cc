#include "DepositsRepository.h"

DepositsRepository::DepositsRepository()
    : _db(AppContext::get<Database>())
{}

DepositsResponse DepositsRepository::findByAccount(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select
                d.id, d.account_id, d.product_id, dp.name as product_name, amount,
                to_char(d.opened_at, 'YYYY-MM-DD"T"HH24:MI:SSZ') as opened_at,
                coalesce(to_char(d.closed_at, 'YYYY-MM-DD"T"HH24:MI:SSZ'), '') as closed_at
            from deposits d
            join deposit_products dp on dp.id = d.product_id
            where d.account_id = $1
            order by d.opened_at desc
        )SQL",
        pqxx::params(accountId)
    );

    DepositsResponse res;
    for (const auto& row : result) {
        res.deposits.push_back({
            row["id"].as<int>(),
            row["account_id"].as<int>(),
            row["product_id"].as<int>(),
            row["product_name"].as<string>(),
            row["amount"].as<double>(),
            row["opened_at"].as<string>(),
            row["closed_at"].as<string>()
        });
    }
    return res;
}

optional<DepositResponse> DepositsRepository::findById(int accountId, int depositId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select
                d.id, d.account_id, d.product_id, dp.name as product_name, d.amount,
                to_char(d.opened_at, 'YYYY-MM-DD"T"HH24:MI:SSZ') as opened_at,
                coalesce(to_char(d.closed_at, 'YYYY-MM-DD"T"HH24:MI:SSZ'), '') as closed_at
            from deposits d
            join deposit_products dp on dp.id = d.product_id
            where d.id = $1 and d.account_id = $2
            limit 1
        )SQL",
        pqxx::params(depositId, accountId)
    );

    if (result.empty()) return nullopt;

    const auto& row = result[0];
    DepositResponse deposit{
        row["id"].as<int>(),
        row["account_id"].as<int>(),
        row["product_id"].as<int>(),
        row["product_name"].as<string>(),
        row["amount"].as<double>(),
        row["opened_at"].as<string>(),
        row["closed_at"].as<string>()
    };
    return deposit;
}
