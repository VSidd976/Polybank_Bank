#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct DepositProduct {
    int _id;
    string _name;
    int _termMonth;
    double _inerestRate;

    nlohmann::json toJson() const;
};

struct DepositProductsResponse {
    vector<DepositProduct> _depositProducts;

    nlohmann::json toJson() const;
};
