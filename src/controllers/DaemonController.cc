#include "DaemonController.h"
#include <format>
using namespace std;

DaemonController::DaemonController(App<AuthMiddleware>& app)
    : BaseController(app)
{}

void DaemonController::registerRoutes() {
    CROW_ROUTE(_app, "/api/daemon/credit-protection").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->createCreditProtection(req);
        });

    CROW_ROUTE(_app, "/api/daemon/credit-protection").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getCreditProtections(req);
        });

    CROW_ROUTE(_app, "/api/daemon/credit-protection/<int>").methods(HTTPMethod::DELETE)
        ([this](const request& req, int id) {
            return this->deleteCreditProtection(req, id);
        });


    CROW_ROUTE(_app, "/api/daemon/leftover-rule").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->createLeftover(req);
        });

    CROW_ROUTE(_app, "/api/daemon/leftover-rule").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getLeftovers(req);
        });

    CROW_ROUTE(_app, "/api/daemon/leftover-rule/<int>").methods(HTTPMethod::DELETE)
        ([this](const request& req, int id) {
            return this->deleteLeftover(req, id);
        });


    CROW_ROUTE(_app, "/api/daemon/auto-transfer").methods(HTTPMethod::POST)
        ([this](const request& req) {
            return this->createAutoTransfer(req);
        });

    CROW_ROUTE(_app, "/api/daemon/auto-transfer").methods(HTTPMethod::GET)
        ([this](const request& req) {
            return this->getAutoTransfers(req);
        });

    CROW_ROUTE(_app, "/api/daemon/auto-transfer/<int>").methods(HTTPMethod::DELETE)
        ([this](const request& req, int id) {
            return this->deleteAutoTransfer(req, id);
        });
}

response DaemonController::createCreditProtection(const request& req) {
    auto dto = parseDto<CreateCreditProtectionRequest>(req);
    if (!dto) return response(400);

    try {
        _service.createCreditProtection(dto.value(), _app.get_context<AuthMiddleware>(req));
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.code = 400;
        res.set_header("Content-Type", "application/json");
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response DaemonController::getCreditProtections(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        auto list = _service.getCreditProtections(_app.get_context<AuthMiddleware>(req));
        nlohmann::json j;
        for (auto& rule : list) j.push_back(rule.toJson());
        res.code = 200;
        res.write(j.dump());
    } catch (const exception& ex) {
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response DaemonController::deleteCreditProtection(const request& req, int id) {
    try {
        _service.deleteCreditProtection(_app.get_context<AuthMiddleware>(req), id);
        return response(200);
    } catch (const exception& ex) {
        return response(400, std::format(R"({{"error":"{}"}})", ex.what()));
    }
}

response DaemonController::createLeftover(const request& req) {
    auto dto = parseDto<CreateLeftoverRuleRequest>(req);
    if (!dto) return response(400);

    try {
        _service.createLeftover(dto.value(), _app.get_context<AuthMiddleware>(req));
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.code = 400;
        res.set_header("Content-Type", "application/json");
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response DaemonController::getLeftovers(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        auto list = _service.getLeftovers(_app.get_context<AuthMiddleware>(req));
        nlohmann::json j;
        for (auto& rule : list) j.push_back(rule.toJson());
        res.code = 200;
        res.write(j.dump());
    } catch (const exception& ex) {
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response DaemonController::deleteLeftover(const request& req, int id) {
    try {
        _service.deleteLeftover(_app.get_context<AuthMiddleware>(req), id);
        return response(200);
    } catch (const exception& ex) {
        return response(400, std::format(R"({{"error":"{}"}})", ex.what()));
    }
}

response DaemonController::createAutoTransfer(const request& req) {
    auto dto = parseDto<CreateAutoTransferRequest>(req);
    if (!dto) return response(400);

    try {
        _service.createAutoTransfer(dto.value(), _app.get_context<AuthMiddleware>(req));
        return response(200);
    } catch (const exception& ex) {
        response res;
        res.code = 400;
        res.set_header("Content-Type", "application/json");
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
        return res;
    }
}

response DaemonController::getAutoTransfers(const request& req) {
    response res;
    res.set_header("Content-Type", "application/json");

    try {
        auto list = _service.getAutoTransfers(_app.get_context<AuthMiddleware>(req));
        nlohmann::json j;
        for (auto& rule : list) j.push_back(rule.toJson());
        res.code = 200;
        res.write(j.dump());
    } catch (const exception& ex) {
        res.code = 400;
        res.write(std::format(R"({{"error":"{}"}})", ex.what()));
    }
    return res;
}

response DaemonController::deleteAutoTransfer(const request& req, int id) {
    try {
        _service.deleteAutoTransfer(_app.get_context<AuthMiddleware>(req), id);
        return response(200);
    } catch (const exception& ex) {
        return response(400, std::format(R"({{"error":"{}"}})", ex.what()));
    }
}
