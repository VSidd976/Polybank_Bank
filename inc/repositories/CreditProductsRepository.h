#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "CreditProductsResponse.h"

class CreditProductsRepository {
public:
    explicit CreditProductsRepository();

    CreditProductsResponse findAll();

private:
    Database& _db;
};
