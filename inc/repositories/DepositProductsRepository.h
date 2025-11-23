#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "DepositProductsResponse.h"

class DepositProductsRepository {
public:
    explicit DepositProductsRepository();

    DepositProductsResponse findAll();

private:
    Database& _db;
};
