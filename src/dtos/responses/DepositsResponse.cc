#include "DepositsResponse.h"

nlohmann::json DepositsResponse::toJson() const {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto& deposit : deposits)
        arr.push_back(deposit.toJson());

    return {{"deposits", arr}};
}
