#include "CreditController.h"
#include "JsonUtils.h"

CreditController::CreditController(App<AuthMiddleware>& app)
    : BaseController(app)
{}

void CreditController::registerRoutes() {
    CROW_ROUTE(_app, "/api/credit/products").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getCreditProducts(req);
        });

    CROW_ROUTE(_app, "/api/credit").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getCredits(req);
        });

    CROW_ROUTE(_app, "/api/credit/<int>").methods(HTTPMethod::GET)
        ([this](const request& req, int id) {
            return this->getCredit(req, id);
        });

    CROW_ROUTE(_app, "/api/credit/pay").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->pay(req);
        });

    CROW_ROUTE(_app, "/api/credit/take").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->take(req);
        });
}

response CreditController::getCreditProducts(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        CreditProductsResponse resDto = _service.getCreditProducts();
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response CreditController::getCredits(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        CreditsResponse resDto = _service.getCredits(_app.get_context<AuthMiddleware>(req));
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response CreditController::getCredit(const request& req, int id) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        CreditResponse resDto = _service.getCredit(_app.get_context<AuthMiddleware>(req), id);
        res.code = 200;
        res.write(resDto.toJson().dump());
    } catch (const exception& ex) {
        res.code = 401;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response CreditController::pay(const request& req){
    auto dto = parseDto<PayCreditRequest>(req);
    if (!dto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        _service.pay(_app.get_context<AuthMiddleware>(req), dto.value());
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response CreditController::take(const request& req) {
    auto dto = parseDto<TakeCreditRequest>(req);
    if (!dto) return response(400);

    response res;
    res.set_header("Content-Type", "application/json");

    try {
        _service.take(_app.get_context<AuthMiddleware>(req), dto.value());
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.set_header("Content-Type", "application/json");
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}
