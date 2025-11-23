#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct OpenDepositRequest {
    int productId;
    double amount;

    static OpenDepositRequest fromJson(const nlohmann::json&);
    bool isValid() const {
        return productId > 0 && amount > 0;
    }
};
