#include "LeftoverRuleResponse.h"

nlohmann::json LeftoverRuleResponse::toJson() const {
    return {
        {"id", id},
        {"trg_card", trgCard},
        {"threshold", threshold},
        {"active", active}
    };
}
