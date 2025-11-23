#include "CreateLeftoverRuleRequest.h"

CreateLeftoverRuleRequest CreateLeftoverRuleRequest::fromJson(const nlohmann::json& json) {
    CreateLeftoverRuleRequest dto;

    dto.trgCard = json.at("trg_card").get<string>();
    dto.threshold = json.at("threshold").get<double>();

    return dto;
}

