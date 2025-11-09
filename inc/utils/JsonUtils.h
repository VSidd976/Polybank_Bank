// #pragma once
// #include <optional>
// #include <drogon/drogon.h>
// using namespace drogon;

#pragma once
#include <nlohmann/json.hpp>
#include <crow.h>
#include <optional>
using namespace crow;

template <typename DTO>
std::optional<DTO> parseDto(const request& req) {
    DTO dto = DTO::fromJson(nlohmann::json::parse(req.body));
    if (dto.isValid()) return dto;
    return std::nullopt;
}


// template <typename DTO>
// std::optional<DTO> parseJsonDto(const HttpRequestPtr& req,
//     std::function<void(const HttpResponsePtr&)>& callback)
// {
//     auto json = req->getJsonObject();
//     if (!json) {
//         auto resp = HttpResponse::newHttpResponse();
//         resp->setStatusCode(k400BadRequest);
//         callback(resp);
//         return std::nullopt;
//     }

//     DTO dto = DTO::fromJson(*json);
//     if (!dto.isValid()) {
//         auto resp = HttpResponse::newHttpResponse();
//         resp->setStatusCode(k400BadRequest);
//         callback(resp);
//         return std::nullopt;
//     }

//     return dto;
// }
