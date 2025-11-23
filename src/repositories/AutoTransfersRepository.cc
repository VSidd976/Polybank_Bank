#include "AutoTransfersRepository.h"
#include <pqxx/pqxx>

AutoTransfersRepository::AutoTransfersRepository()
    : _db(AppContext::get<Database>())
{}

bool AutoTransfersRepository::createRule(
    int srcId, int trgId, double amount,
    const string& periodicity, const string& nextRunDate)
{
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            R"SQL(
                insert into auto_transfers(src_account_id, trg_account_id, amount, periodicity, next_run_date, active)
                values ($1, $2, $3, $4, $5, true)
            )SQL",
            pqxx::params(srcId, trgId, amount, periodicity, nextRunDate)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}

vector<AutoTransferResponse> AutoTransfersRepository::findByAccount(int accountId) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select at.id, c.card as trg_card,
                   coalesce(at.amount,0) as amount,
                   at.periodicity, to_char(at.next_run_date, 'YYYY-MM-DD') as next_run_date,
                   at.active
            from auto_transfers at
            join accounts a on a.id = at.src_account_id
            join accounts b on b.id = at.trg_account_id
            join cards c on c.account_id = b.id
            where at.src_account_id = $1
        )SQL",
        pqxx::params(accountId)
    );

    vector<AutoTransferResponse> res;
    for (const auto& row : result) {
        res.push_back({
            row["id"].as<int>(),
            row["trg_card"].as<string>(),
            row["amount"].as<double>(),
            row["periodicity"].as<string>(),
            row["next_run_date"].as<string>(),
            row["active"].as<bool>()
        });
    }
    return res;
}

bool AutoTransfersRepository::disableRule(int id, int accountId) {
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            "update auto_transfers set active = false where id = $1 and src_account_id = $2",
            pqxx::params(id, accountId)
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}
