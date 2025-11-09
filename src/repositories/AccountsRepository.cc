#include "AccountsRepository.h"

AccountsRepository::AccountsRepository()
    : _db(AppContext::get<Database>())
{}

optional<AccountResponse> AccountsRepository::findById(int account_id) {
    pqxx::work tx(_db.getConn());
    auto result = tx.exec(
        R"SQL(
            select cl.full_name, a.balance
            from accounts a
            join clients cl on a.client_id = cl.id
            where a.id = $1
        )SQL",
        pqxx::params(account_id)
    );

    if (result.empty()) return nullopt;

    const auto& row = result[0];
    return AccountResponse(
        row["full_name"].as<string>(),
        row["balance"].as<double>()
    );
}

bool AccountsRepository::hasEnoughBalance(int account_id, double amount) {
    pqxx::work tx(_db.getConn());

    auto result = tx.exec(
        R"SQL(
            select balance
            from accounts
            where id = $1
        )SQL",
        pqxx::params(account_id)
    );

    if (result.empty()) return false;
    return result[0]["balance"].as<double>() >= amount;
}
