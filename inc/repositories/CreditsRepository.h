#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "CreditResponse.h"
#include "CreditsResponse.h"

class CreditsRepository {
public:
    explicit CreditsRepository();

    CreditsResponse findByAccount(int);
    optional<CreditResponse> findById(int, int);

private:
    Database& _db;
};
