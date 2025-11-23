#pragma once
#include <nlohmann/json.hpp>
#include <crow.h>
#include <optional>
using namespace crow;
using namespace std;

template <typename DTO>
optional<DTO> parseDto(const request& req) {
    DTO dto = DTO::fromJson(nlohmann::json::parse(req.body));
    if (dto.isValid()) return dto;
    return nullopt;
}
