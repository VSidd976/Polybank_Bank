#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct DepositResponse {
    int id;
    int accountId;
    int productId;
    string productName;
    double amount;
    string openedAt;
    string closedAt;

    nlohmann::json toJson() const;
};
