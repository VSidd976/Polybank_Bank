#pragma once
#include <nlohmann/json.hpp>
using namespace std;

struct CloseDepositRequest {
    int _deposit_id;

    static CloseDepositRequest fromJson(const nlohmann::json&);
    bool isValid() const {
        return _deposit_id > 0;
    }
};
