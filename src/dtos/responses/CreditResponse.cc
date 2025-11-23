#include "CreditResponse.h"

nlohmann::json CreditResponse::toJson() const {
    nlohmann::json json = {
        {"id", id},
        {"account_id", accountId},
        {"product_id", productId},
        {"product_name", productName},
        {"amount", amount},
        {"interest_accrued", interestAccrued},
        {"remaining_amount", remainingAmount},
        {"opened_at", openedAt}
    };

    if (!closedAt.empty())
        json["closed_at"] = closedAt;
    else
        json["closed_at"] = nullptr;

    return json;
}
