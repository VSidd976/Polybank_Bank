#include "AccountRequest.h"

AccountRequest AccountRequest::fromJson(const nlohmann::json& json) {
    AccountRequest dto;

    dto.amount = json.at("amount").get<double>();
    return dto;
}
