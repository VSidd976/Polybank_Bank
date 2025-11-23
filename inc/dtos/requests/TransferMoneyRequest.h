#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct TransferMoneyRequest {
    string to;
    double amount;

    static TransferMoneyRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !to.empty() && amount != 0;
    }
};
