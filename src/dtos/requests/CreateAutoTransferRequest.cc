#include "CreateAutoTransferRequest.h"

CreateAutoTransferRequest CreateAutoTransferRequest::fromJson(const nlohmann::json& json) {
    CreateAutoTransferRequest dto;

    dto.trgCard = json.at("trg_account_id").get<string>();
    dto.amount = json.at("amount").get<double>();
    dto.periodicity = json.at("periodicity").get<string>();
    dto.nextRunDate = json.at("next_run_date").get<string>();
    return dto;
}
