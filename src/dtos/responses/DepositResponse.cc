#include "DepositResponse.h"

nlohmann::json DepositResponse::toJson() const {
    nlohmann::json json = {
        {"id", _id},
        {"account_id", _account_id},
        {"product_id", _product_id},
        {"amount", _amount},
        {"opened_at", _opened_at}
    };

    if (!_closed_at.empty())
        json["closed_at"] = _closed_at;
    else
        json["closed_at"] = nullptr;

    return json;
}
