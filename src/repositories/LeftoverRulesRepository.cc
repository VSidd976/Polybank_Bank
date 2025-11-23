#include "LeftoverRulesRepository.h"
#include <pqxx/pqxx>

LeftoverRulesRepository::LeftoverRulesRepository()
    : _db(AppContext::get<Database>())
{}

bool LeftoverRulesRepository::createRule(int srcId, int trgId, double threshold) {
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            R"SQL(
                insert into leftover_rules(src_account_id, trg_account_id, threshold, active)
                values ($1, $2, $3, true)
            )SQL",
            pqxx::params(srcId, trgId, threshold)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}

vector<LeftoverRuleResponse> LeftoverRulesRepository::findByAccount(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select lr.id,
                   c.card as trg_card,
                   lr.threshold,
                   lr.active
            from leftover_rules lr
            join accounts trg on trg.id = lr.trg_account_id
            join cards c on c.account_id = trg.id
            where lr.src_account_id = $1
        )SQL",
        pqxx::params(accountId)
    );

    vector<LeftoverRuleResponse> res;
    for (const auto& row : result) {
        res.push_back({
            row["id"].as<int>(),
            row["trg_card"].as<std::string>(),
            row["threshold"].as<double>(),
            row["active"].as<bool>()
        });
    }
    return res;
}

bool LeftoverRulesRepository::disableRule(int id, int accountId) {
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            "update leftover_rules set active = false where id = $1 and src_account_id = $2",
            pqxx::params(id, accountId)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}
