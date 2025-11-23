#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct LeftoverRuleResponse {
    int id;
    string trgCard;
    double threshold;
    bool active;

    nlohmann::json toJson() const;
};
