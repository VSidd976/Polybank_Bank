#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "AutoTransferResponse.h"
#include <vector>
using namespace std;

class AutoTransfersRepository {
public:
    explicit AutoTransfersRepository();

    bool createRule(int, int, double, const string&, const string&);
    vector<AutoTransferResponse> findByAccount(int);
    bool disableRule(int, int);

private:
    Database& _db;
};
