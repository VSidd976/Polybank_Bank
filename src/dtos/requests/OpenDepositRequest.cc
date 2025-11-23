#include "OpenDepositRequest.h"

OpenDepositRequest OpenDepositRequest::fromJson(const nlohmann::json& json) {
    OpenDepositRequest dto;

    dto.productId = json.at("product_id").get<int>();
    dto.amount = json.at("amount").get<double>();
    return dto;
}
