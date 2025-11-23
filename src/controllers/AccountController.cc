#include "AccountController.h"
#include "JsonUtils.h"

AccountController::AccountController(App<AuthMiddleware>& app)
    : BaseController(app)
{}

void AccountController::registerRoutes() {
    CROW_ROUTE(_app, "/api/account").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getAccount(req);
        });

    CROW_ROUTE(_app, "/api/account/put").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->putMoney(req);
        });

    CROW_ROUTE(_app, "/api/account/take").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->takeMoney(req);
        });

    CROW_ROUTE(_app, "/api/account/transfer").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->transferMoney(req);
        });
}

response AccountController::getAccount(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        AccountResponse resDto = _service.getAccount(_app.get_context<AuthMiddleware>(req));
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response AccountController::putMoney(const request& req) {
    auto dto = parseDto<AccountRequest>(req);
    if (!dto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        _service.putMoney(dto.value(), _app.get_context<AuthMiddleware>(req));
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response AccountController::takeMoney(const request& req) {
    auto dto = parseDto<AccountRequest>(req);
    if (!dto) return response(400);

    try {
        _service.takeMoney(dto.value(), _app.get_context<AuthMiddleware>(req));
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response AccountController::transferMoney(const request& req) {
    auto dto = parseDto<TransferMoneyRequest>(req);
    if (!dto) return response(400);

    try {
        _service.transferMoney(dto.value(), _app.get_context<AuthMiddleware>(req));
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}
