#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct AccountResponse {
    string _full_name;
    double _balance;

    nlohmann::json toJson() const;
};
