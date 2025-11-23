#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CloseDepositRequest {
    int depositId;

    static CloseDepositRequest fromJson(const nlohmann::json&);
    bool isValid() const {
        return depositId > 0;
    }
};
