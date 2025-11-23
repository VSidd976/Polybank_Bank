#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CreditResponse {
    int id;
    int accountId;
    int productId;
    string productName;
    double amount;
    double interestAccrued;
    double remainingAmount;
    string openedAt;
    string closedAt;

    nlohmann::json toJson() const;
};
