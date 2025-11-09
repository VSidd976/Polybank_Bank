#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct VerifyCredentialsRequest {
    std::string _card;
    std::string _pin;

    static VerifyCredentialsRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !_card.empty() && !_pin.empty();
    }
};
