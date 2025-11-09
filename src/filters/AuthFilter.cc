// #include "AuthFilter.h"
// #include "JwtUtils.h"

// void AuthFilter::doFilter(const HttpRequestPtr& req,
//     FilterCallback&& fcb,
//     FilterChainCallback&& fccb)
// {
//     const auto &path = req->path();
//     if (path.rfind("/api/auth", 0) == 0) {
//         fccb();
//         return;
//     }

//     auto authHeader = req->getHeader("Authorization");
//     if (authHeader.empty() || authHeader.find("Bearer ") != 0) {
//         auto resp = HttpResponse::newHttpResponse();
//         resp->setStatusCode(k401Unauthorized);
//         fcb(resp);
//         return;
//     }

//     std::string card;
//     if (!JwtUtils::verifyToken(authHeader.substr(7), card)) {
//         auto resp = HttpResponse::newHttpResponse();
//         resp->setStatusCode(k401Unauthorized);
//         fcb(resp);
//         return;
//     }

//     req->getAttributes()->insert("card", card);
//     fccb();
// }
