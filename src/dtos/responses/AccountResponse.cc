#include "AccountResponse.h"

nlohmann::json AccountResponse::toJson() const {
    return {
        {"full_name", _full_name},
        {"balance", _balance}
    };
}
