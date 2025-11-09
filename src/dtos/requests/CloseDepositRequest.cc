#include "CloseDepositRequest.h"

CloseDepositRequest CloseDepositRequest::fromJson(const nlohmann::json& json) {
    CloseDepositRequest dto;

    dto._deposit_id = json.at("deposit_id").get<int>();
    return dto;
}
