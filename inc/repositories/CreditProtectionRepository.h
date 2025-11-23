#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "CreditProtectionResponse.h"
using namespace std;

class CreditProtectionRepository {
public:
    explicit CreditProtectionRepository();

    bool createRule(int, int, double);
    vector<CreditProtectionResponse> findByAccount(int);
    bool disableRule(int, int);

private:
    Database& _db;
};
