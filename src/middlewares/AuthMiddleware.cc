#include "AuthMiddleware.h"
#include "JwtUtils.h"

void AuthMiddleware::before_handle(request& req, response& res, context& ctx) {
    static const vector<string> prefixes = {
        "/api/auth",
        "/api/docs",
        "/static"
    };

    bool allowed = any_of(
        prefixes.begin(),
        prefixes.end(),
        [&](const string& prefix){
            return req.url.starts_with(prefix);
        }
    );
    if (allowed) return;

    auto it = req.headers.find("Authorization");
    if (it == req.headers.end() || it->second.find("Bearer ") != 0) {
        res.code = 401;
        res.end();
        return;
    }

    if (!JwtUtils::verifyToken(it->second.substr(7), ctx.cardId, ctx.accountId, ctx.clientId)) {
        res.code = 401;
        res.end();
        return;
    }
}

void AuthMiddleware::after_handle(request& req, response& res, context& ctx) {
    return;
}
