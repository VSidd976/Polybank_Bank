#pragma once
#include <nlohmann/json.hpp>

struct VerifyCardResponse {
    bool valid;

    nlohmann::json toJson() const;
};
