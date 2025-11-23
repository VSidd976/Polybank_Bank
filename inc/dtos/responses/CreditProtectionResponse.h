#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CreditProtectionResponse {
    int id;
    string backupCard;
    double minBalance;
    bool active;

    nlohmann::json toJson() const;
};
