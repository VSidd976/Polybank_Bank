#include "VerifyCredentialsRequest.h"

VerifyCredentialsRequest VerifyCredentialsRequest::fromJson(const nlohmann::json& json) {
    VerifyCredentialsRequest dto;

    dto._card = json.at("card").get<string>();
    dto._pin = json.at("pin").get<string>();
    return dto;
}
