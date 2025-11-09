#include "TransferMoneyRequest.h"

TransferMoneyRequest TransferMoneyRequest::fromJson(const nlohmann::json& json) {
    TransferMoneyRequest dto;

    dto._to = json.at("to").get<string>();
    // dto._from = json.at("from").get<string>();
    dto._amount = json.at("amount").get<double>();
    return dto;
}
