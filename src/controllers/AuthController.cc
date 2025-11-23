#include "AuthController.h"
#include "JsonUtils.h"

AuthController::AuthController(App<AuthMiddleware>& app)
    : BaseController(app)
{}

void AuthController::registerRoutes() {
    CROW_ROUTE(_app, "/api/auth/verify-credentials").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->verifyCredentials(req);
        });

    CROW_ROUTE(_app, "/api/auth/verify-card").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->verifyCard(req);
        });
}

response AuthController::verifyCredentials(const request& req) {
    auto reqDto = parseDto<VerifyCredentialsRequest>(req);
    if (!reqDto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        VerifyCredentialsResponse resDto = _service.verifyCredentials(reqDto.value());
        res.code = 200;
        res.write(resDto.toJson().dump());

    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response AuthController::verifyCard(const request& req) {
    auto reqDto = parseDto<VerifyCardRequest>(req);
    if (!reqDto) return response(400);

    VerifyCardResponse resDto = _service.verifyCard(reqDto.value());

    response res;
    res.set_header("Content-Type", "application/json");
    res.code = 200;
    res.write(resDto.toJson().dump());
    return res;
}
