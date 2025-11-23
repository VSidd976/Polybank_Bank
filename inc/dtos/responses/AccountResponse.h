#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct AccountResponse {
    string fullName;
    double balance;

    nlohmann::json toJson() const;
};
