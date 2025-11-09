#pragma once
#include "Database.h"
#include "AppContext.h"
#include "DepositResponse.h"
#include "DepositsResponse.h"

class DepositsRepository {
public:
    explicit DepositsRepository();

    DepositsResponse findByAccount(int);
    optional<DepositResponse> findById(int, int);

    bool openDeposit(int, int, double);
    bool closeDeposit(int, int);

private:
    Database& _db;
};
