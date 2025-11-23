#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct VerifyCredentialsRequest {
    string card;
    string pin;

    static VerifyCredentialsRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !card.empty() && !pin.empty();
    }
};
