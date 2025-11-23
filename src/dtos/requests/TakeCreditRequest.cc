#include "TakeCreditRequest.h"

TakeCreditRequest TakeCreditRequest::fromJson(const nlohmann::json& json) {
    TakeCreditRequest dto;

    dto.productId = json.at("product_id").get<int>();
    dto.amount = json.at("amount").get<double>();
    return dto;
}
