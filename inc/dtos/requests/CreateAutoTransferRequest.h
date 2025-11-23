#pragma once
#include <string>
#include <nlohmann/json.hpp>
using namespace std;

struct CreateAutoTransferRequest {
    string trgCard;
    double amount;
    string periodicity;
    string nextRunDate;

    static CreateAutoTransferRequest fromJson(const nlohmann::json&);
    bool isValid() const {
        return !trgCard.empty() && amount > 0 && !periodicity.empty() && !nextRunDate.empty();
    }
};
