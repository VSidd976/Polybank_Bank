#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct TransferMoneyRequest {
    string _to;
    // string _from;
    double _amount;

    static TransferMoneyRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !_to.empty() && _amount != 0;
    }
};
