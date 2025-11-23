#include "VerifyCardRequest.h"

VerifyCardRequest VerifyCardRequest::fromJson(const nlohmann::json& json) {
    VerifyCardRequest dto;

    dto.card = json.at("card").get<string>();
    return dto;
}
