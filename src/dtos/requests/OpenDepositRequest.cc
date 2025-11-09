#include "OpenDepositRequest.h"

OpenDepositRequest OpenDepositRequest::fromJson(const nlohmann::json& json) {
    OpenDepositRequest dto;

    dto._product_id = json.at("product_id").get<int>();
    dto._amount = json.at("amount").get<double>();
    return dto;
}
