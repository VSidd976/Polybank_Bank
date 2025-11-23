#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct TakeCreditRequest {
    int productId;
    double amount;

    static TakeCreditRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return productId > 0 && amount > 0;
    }
};
