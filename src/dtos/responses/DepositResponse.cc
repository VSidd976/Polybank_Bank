#include "DepositResponse.h"

nlohmann::json DepositResponse::toJson() const {
    nlohmann::json json = {
        {"id", id},
        {"account_id", accountId},
        {"product_id", productId},
        {"amount", amount},
        {"opened_at", openedAt}
    };

    if (!closedAt.empty())
        json["closed_at"] = closedAt;
    else
        json["closed_at"] = nullptr;

    return json;
}
