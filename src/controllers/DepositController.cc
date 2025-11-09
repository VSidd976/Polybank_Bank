#include "DepositController.h"
#include "JsonUtils.h"

DepositController::DepositController(App<AuthMiddleware>& app)
    : BaseController(app)
{}

void DepositController::registerRoutes() {
    CROW_ROUTE(_app, "/api/deposit/products").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getDepositProducts(req);
        });

    CROW_ROUTE(_app, "/api/deposit").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getDeposits(req, _app.get_context<AuthMiddleware>(req));
        });

    CROW_ROUTE(_app, "/api/deposit/<int>").methods(HTTPMethod::GET)
        ([this](const request& req, int id) {
            return this->getDeposit(req, id, _app.get_context<AuthMiddleware>(req));
        });

    CROW_ROUTE(_app, "/api/deposit/put").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->putOn(req, _app.get_context<AuthMiddleware>(req));
        });

    CROW_ROUTE(_app, "/api/deposit/take").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->takeFrom(req, _app.get_context<AuthMiddleware>(req));
        });
}

response DepositController::getDepositProducts(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        DepositProductsResponse resDto = _service.getDepositProducts();
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response DepositController::getDeposits(const request& req, AuthMiddleware::context& ctx) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        DepositsResponse resDto = _service.getDeposits(ctx);
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response DepositController::getDeposit(const request& req, int id, AuthMiddleware::context& ctx) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        DepositResponse resDto = _service.getDeposit(ctx, id);
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response DepositController::putOn(const request& req, AuthMiddleware::context& ctx){
    auto dto = parseDto<OpenDepositRequest>(req);
    if (!dto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        _service.putOn(ctx, dto.value());
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response DepositController::takeFrom(const request& req, AuthMiddleware::context& ctx) {
    auto dto = parseDto<CloseDepositRequest>(req);
    if (!dto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        _service.takeFrom(ctx, dto.value());
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}
