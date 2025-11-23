#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct DepositProduct {
    int id;
    string name;
    int termMonth;
    double inerestRate;

    nlohmann::json toJson() const;
};

struct DepositProductsResponse {
    vector<DepositProduct> depositProducts;

    nlohmann::json toJson() const;
};
