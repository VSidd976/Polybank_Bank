#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct PayCreditRequest {
    int creditId;
    double amount;

    static PayCreditRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return creditId > 0 && amount > 0;
    }
};
