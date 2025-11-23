#include "PayCreditRequest.h"

PayCreditRequest PayCreditRequest::fromJson(const nlohmann::json& json) {
    PayCreditRequest dto;

    dto.creditId = json.at("credit_id").get<int>();
    dto.amount = json.at("amount").get<double>();
    return dto;
}
