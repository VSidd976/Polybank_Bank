#include "AuthMiddleware.h"
#include "JwtUtils.h"

void AuthMiddleware::before_handle(request& req, response& res, context& ctx) {
    if (req.url.rfind("/api/auth", 0) == 0) {
        return;
    }

    auto it = req.headers.find("Authorization");
    if (it == req.headers.end() || it->second.find("Bearer ") != 0) {
        res.code = 401;
        res.end();
        return;
    }

    if (!JwtUtils::verifyToken(it->second.substr(7), ctx._card_id, ctx._account_id, ctx._client_id)) {
        res.code = 401;
        res.end();
        return;
    }
}

void AuthMiddleware::after_handle(request& req, response& res, context& ctx) {
    return;
}
