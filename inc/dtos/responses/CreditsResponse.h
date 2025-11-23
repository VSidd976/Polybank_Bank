#pragma once
#include <nlohmann/json.hpp>
#include "CreditResponse.h"
using namespace std;

struct CreditsResponse {
    vector<CreditResponse> credits;

    nlohmann::json toJson() const;
};
