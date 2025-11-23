#include "AccountResponse.h"

nlohmann::json AccountResponse::toJson() const {
    return {
        {"full_name", fullName},
        {"balance", balance}
    };
}
