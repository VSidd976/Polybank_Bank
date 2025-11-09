#include "VerifyCredentialsResponse.h"

nlohmann::json VerifyCredentialsResponse::toJson() const {
    return {{"token", _token}};
}
