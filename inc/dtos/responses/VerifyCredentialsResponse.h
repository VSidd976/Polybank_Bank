#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct VerifyCredentialsResponse {
    string token;

    nlohmann::json toJson() const;
};
