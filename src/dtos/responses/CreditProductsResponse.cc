#include "CreditProductsResponse.h"

nlohmann::json CreditProduct::toJson() const {
    return {
        {"id", id},
        {"name", name},
        {"term_months", termMonth},
        {"interest_rate", inerestRate}
    };
}

nlohmann::json CreditProductsResponse::toJson() const {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& product : creditProducts)
        arr.push_back(product.toJson());

    return {{"credit_products", arr}};
}
