#include "CreateCreditProtectionRequest.h"

CreateCreditProtectionRequest CreateCreditProtectionRequest::fromJson(const nlohmann::json& json) {
    CreateCreditProtectionRequest dto;

    dto.backupCard = json.at("backup_card").get<string>();
    dto.minBalance = json.at("min_balance").get<double>();
    return dto;
}
