#include "CloseDepositRequest.h"

CloseDepositRequest CloseDepositRequest::fromJson(const nlohmann::json& json) {
    CloseDepositRequest dto;

    dto.depositId = json.at("deposit_id").get<int>();
    return dto;
}
