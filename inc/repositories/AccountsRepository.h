#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "AccountResponse.h"

class AccountsRepository {
public:
    explicit AccountsRepository();

    optional<AccountResponse> findById(int);
    optional<double> getBalanceById(int);

private:
    Database& _db;
};
