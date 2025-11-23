#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CreateLeftoverRuleRequest {
    string trgCard;
    double threshold;

    static CreateLeftoverRuleRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !trgCard.empty() && threshold > 0;
    }
};
