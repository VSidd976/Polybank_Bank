#include "CreditsResponse.h"

nlohmann::json CreditsResponse::toJson() const {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& credit : credits)
        arr.push_back(credit.toJson());

    return {{"credits", arr}};
}
