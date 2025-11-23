#include "AutoTransferResponse.h"

nlohmann::json AutoTransferResponse::toJson() const {
    return {
        {"id", id},
        {"trg_card", trgCard},
        {"amount", amount},
        {"periodicity", periodicity},
        {"next_run_date", nextRunDate},
        {"active", active}
    };
}
