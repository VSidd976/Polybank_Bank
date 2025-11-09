#pragma once
#include <nlohmann/json.hpp>
#include "DepositResponse.h"
using namespace std;

struct DepositsResponse {
    vector<DepositResponse> _deposits;

    nlohmann::json toJson() const;
};
