#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct AutoTransferResponse {
    int id;
    string trgCard;
    double amount;
    string periodicity;
    string nextRunDate;
    bool active;

    nlohmann::json toJson() const;
};
