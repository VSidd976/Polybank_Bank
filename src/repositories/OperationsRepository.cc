#include "OperationsRepository.h"

OperationsRepository::OperationsRepository()
    : _db(AppContext::get<Database>())
{}

bool OperationsRepository::addTransfer(int srcId, int trgId, double amount)
{
    return addOperation(
        srcId,
        trgId,
        nullopt,
        nullopt,
        amount,
        "transfer"
    );
}

bool OperationsRepository::addAtmWithdraw(int srcId, double amount)
{
    return addOperation(
        srcId,
        nullopt,
        "atm",
        nullopt,
        amount,
        "atm_withdraw"
    );
}

bool OperationsRepository::addAtmDeposit(int trgId, double amount)
{
    return addOperation(
        nullopt,
        trgId,
        "atm",
        nullopt,
        amount,
        "atm_deposit"
    );
}

bool OperationsRepository::addDepositOpen(int accountId, int productId, double amount)
{
    return addOperation(
        accountId,
        nullopt,
        "deposit",
        productId,
        amount,
        "deposit_open"
    );
}

bool OperationsRepository::addDepositClose(int accountId, int depositId)
{
    return addOperation(
        accountId,
        nullopt,
        "deposit",
        depositId,
        0,
        "deposit_close"
    );
}

bool OperationsRepository::addCreditTake(int accountId, int productId, double amount)
{
    return addOperation(
        nullopt,
        accountId,
        "credit",
        productId,
        amount,
        "credit_issue"
    );
}

bool OperationsRepository::addCreditPay(int accountId, int creditId, double amount)
{
    return addOperation(
        accountId,
        nullopt,
        "credit",
        creditId,
        amount,
        "credit_payment"
    );
}

bool OperationsRepository::addOperation(
    optional<int> src,
    optional<int> trg,
    optional<string> entityType,
    optional<int> entityId,
    double amount,
    const string& type)
{
    try {
        DbTransaction tx(_db);
        tx.tx().exec(
            R"SQL(
                insert into operations(
                    src_account_id, trg_account_id,
                    entity_type, entity_id,
                    amount, type
                )
                values ($1, $2, $3, $4, $5, $6)
            )SQL",
            pqxx::params(
                src, trg,
                entityType, entityId,
                amount, type
            )
        );
        tx.commit();
        return true;
    } catch (const exception&) {
        return false;
    }
}
