#include "CreditProtectionRepository.h"
#include <pqxx/pqxx>

CreditProtectionRepository::CreditProtectionRepository()
    : _db(AppContext::get<Database>())
{}

bool CreditProtectionRepository::createRule(int protectedId, int backupId, double minBalance) {
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            R"SQL(
                insert into credit_protection_rules(protected_account_id, backup_account_id, min_balance, active)
                values ($1, $2, $3, true)
            )SQL",
            pqxx::params(protectedId, backupId, minBalance)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}

vector<CreditProtectionResponse> CreditProtectionRepository::findByAccount(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select cpr.id,
                   c.card as backup_card,
                   cpr.min_balance,
                   cpr.active
            from credit_protection_rules cpr
            join accounts backup on backup.id = cpr.backup_account_id
            join cards c on c.account_id = backup.id
            where cpr.protected_account_id = $1
        )SQL",
        pqxx::params(accountId)
    );

    vector<CreditProtectionResponse> res;
    for (const auto& row : result) {
        res.push_back({
            row["id"].as<int>(),
            row["backup_card"].as<std::string>(),
            row["min_balance"].as<double>(),
            row["active"].as<bool>()
        });
    }
    return res;
}

bool CreditProtectionRepository::disableRule(int id, int accountId) {
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            "update credit_protection_rules set active = false where id = $1 and protected_account_id = $2",
            pqxx::params(id, accountId)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}
