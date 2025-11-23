#pragma once
#include <nlohmann/json.hpp>
#include "crow.h"
using namespace std;

struct VerifyCardRequest {
    string card;

    static VerifyCardRequest fromJson(const nlohmann::json& json);
    bool isValid() const {
        return !card.empty();
    }
};
