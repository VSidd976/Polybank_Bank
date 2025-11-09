#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct DepositResponse {
    int _id;
    int _account_id;
    int _product_id;
    double _amount;
    string _opened_at;
    string _closed_at;

    nlohmann::json toJson() const;
};
