#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct AccountRequest {
    double _amount;

    static AccountRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return _amount != 0;
    }
};
