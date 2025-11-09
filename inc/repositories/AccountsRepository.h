#pragma once
#include "Database.h"
#include "AppContext.h"
#include "AccountResponse.h"

class AccountsRepository {
public:
    explicit AccountsRepository();

    optional<AccountResponse> findById(int);

    bool hasEnoughBalance(int, double);

private:
    Database& _db;

};
