#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "DepositResponse.h"
#include "DepositsResponse.h"

class DepositsRepository {
public:
    explicit DepositsRepository();

    DepositsResponse findByAccount(int);
    optional<DepositResponse> findById(int, int);

private:
    Database& _db;
};
