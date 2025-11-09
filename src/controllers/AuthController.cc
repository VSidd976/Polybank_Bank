#include "AuthController.h"
#include "JsonUtils.h"

AuthController::AuthController(App<AuthMiddleware>& app)
    : BaseController(app)
    // : _app(app), _service(AppContext::get<AuthService>())
{}

void AuthController::registerRoutes() {
    CROW_ROUTE(_app, "/api/auth/verify-credentials").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->verifyCredentials(req);
        });
}

response AuthController::verifyCredentials(const request& req) {
    auto reqDto = parseDto<VerifyCredentialsRequest>(req);
    if (!reqDto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        VerifyCredentialsResponse resDto = _service.verify(reqDto.value());
        res.code = 200;
        res.write(resDto.toJson().dump());

    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}
