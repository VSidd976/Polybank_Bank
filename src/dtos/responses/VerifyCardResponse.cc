#include "VerifyCardResponse.h"

nlohmann::json VerifyCardResponse::toJson() const {
    return {{"valid", valid}};
}
