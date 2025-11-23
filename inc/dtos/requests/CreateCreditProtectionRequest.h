#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CreateCreditProtectionRequest {
    string backupCard;
    double minBalance;

    static CreateCreditProtectionRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !backupCard.empty() > 0 && minBalance >= 0;
    }
};
