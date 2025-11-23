#pragma once
#include "VerifyCredentialsRequest.h"
#include "VerifyCardRequest.h"
#include "AuthService.h"
#include "AuthMiddleware.h"
#include "AppContext.h"
#include "BaseController.h"
#include "crow.h"
using namespace std;
using namespace crow;

class AuthController : public BaseController<AuthService> {
public:
    explicit AuthController(App<AuthMiddleware>&);

    void registerRoutes() override;

private:
    response verifyCredentials(const request&);
    response verifyCard(const request&);
};
