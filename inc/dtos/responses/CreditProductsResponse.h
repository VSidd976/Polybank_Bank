#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CreditProduct {
    int id;
    string name;
    int termMonth;
    double inerestRate;

    nlohmann::json toJson() const;
};

struct CreditProductsResponse {
    vector<CreditProduct> creditProducts;

    nlohmann::json toJson() const;
};
