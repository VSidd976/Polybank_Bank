#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "LeftoverRuleResponse.h"
using namespace std;

class LeftoverRulesRepository {
public:
    explicit LeftoverRulesRepository();

    bool createRule(int, int, double);
    vector<LeftoverRuleResponse> findByAccount(int);
    bool disableRule(int, int);

private:
    Database& _db;
};
