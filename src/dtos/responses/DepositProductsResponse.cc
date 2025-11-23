#include "DepositProductsResponse.h"

nlohmann::json DepositProduct::toJson() const {
    return {
        {"id", id},
        {"name", name},
        {"term_months", termMonth},
        {"interest_rate", inerestRate}
    };
}

nlohmann::json DepositProductsResponse::toJson() const {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& product : depositProducts)
        arr.push_back(product.toJson());

    return {{"deposit_products", arr}};
}
