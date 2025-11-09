#include "OperationsRepository.h"

OperationsRepository::OperationsRepository()
    : _db(AppContext::get<Database>())
{}

bool OperationsRepository::addOperation(
    optional<int> from_id, optional<int> to_id,
    double amount, const string& type)
{
    try {
        pqxx::work tx(_db.getConn());
        tx.exec(
            "insert into operations(from_account_id, to_account_id, amount, type) "
            "values ($1, $2, $3, $4)",
            pqxx::params(from_id,
                to_id,
                amount,
                type
            )
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}
