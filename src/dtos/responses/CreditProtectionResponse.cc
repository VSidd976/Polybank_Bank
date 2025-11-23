#include "CreditProtectionResponse.h"

nlohmann::json CreditProtectionResponse::toJson() const {
    return {
        {"id", id},
        {"backup_card", backupCard},
        {"min_balance", minBalance},
        {"active", active}
    };
}
