#pragma once
#include "DbTransaction.h"
#include "AppContext.h"

class OperationsRepository {
public:
    explicit OperationsRepository();

    bool addTransfer(int, int, double);
    bool addAtmWithdraw(int, double);
    bool addAtmDeposit(int, double);

    bool addDepositOpen(int, int, double);
    bool addDepositClose(int, int);

    bool addCreditTake(int, int, double);
    bool addCreditPay(int, int, double);

private:
    Database& _db;

    bool addOperation(
        optional<int>, optional<int>, optional<string>,
        optional<int>, double, const string&
    );
};
