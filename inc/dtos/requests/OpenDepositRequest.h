#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct OpenDepositRequest {
    int _product_id;
    double _amount;

    static OpenDepositRequest fromJson(const nlohmann::json&);
    bool isValid() const {
        return _product_id > 0 && _amount > 0;
    }
};
