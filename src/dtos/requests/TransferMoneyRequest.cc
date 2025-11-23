#include "TransferMoneyRequest.h"

TransferMoneyRequest TransferMoneyRequest::fromJson(const nlohmann::json& json) {
    TransferMoneyRequest dto;

    dto.to = json.at("to").get<string>();
    dto.amount = json.at("amount").get<double>();
    return dto;
}
