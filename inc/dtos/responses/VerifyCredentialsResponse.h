#pragma once
#include <nlohmann/json.hpp>

struct VerifyCredentialsResponse {
    std::string _token;

    nlohmann::json toJson() const;
};
