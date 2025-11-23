#include "VerifyCredentialsRequest.h"

VerifyCredentialsRequest VerifyCredentialsRequest::fromJson(const nlohmann::json& json) {
    VerifyCredentialsRequest dto;

    dto.card = json.at("card").get<string>();
    dto.pin = json.at("pin").get<string>();
    return dto;
}
