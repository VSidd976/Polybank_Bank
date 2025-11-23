#include "AccountsRepository.h"

AccountsRepository::AccountsRepository()
    : _db(AppContext::get<Database>())
{}

optional<AccountResponse> AccountsRepository::findById(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select cl.full_name, a.balance
            from accounts a
            join clients cl on a.client_id = cl.id
            where a.id = $1
        )SQL",
        pqxx::params(accountId)
    );

    if (result.empty()) return nullopt;
    return AccountResponse(
        result[0]["full_name"].as<string>(),
        result[0]["balance"].as<double>()
    );
}

optional<double> AccountsRepository::getBalanceById(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select balance
            from accounts
            where id = $1
        )SQL",
        pqxx::params(accountId)
    );

    if (result.empty()) return nullopt;
    return result[0]["balance"].as<double>();
}
