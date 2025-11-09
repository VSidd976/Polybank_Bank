#include "DepositProductsResponse.h"

nlohmann::json DepositProduct::toJson() const {
    return {
        {"id", _id},
        {"name", _name},
        {"term_months", _termMonth},
        {"interest_rate", _inerestRate}
    };
}

nlohmann::json DepositProductsResponse::toJson() const {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& product : _depositProducts)
        arr.push_back(product.toJson());

    return {{"deposit_products", arr}};
}
