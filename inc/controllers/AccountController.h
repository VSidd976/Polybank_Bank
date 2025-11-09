#pragma once
#include "AccountService.h"
#include "BaseController.h"
#include "AuthMiddleware.h"
#include "AppContext.h"
#include "crow.h"
using namespace std;
using namespace crow;

class AccountController : public BaseController<AccountService> {
public:
    explicit AccountController(App<AuthMiddleware>&);

    void registerRoutes() override;

private:
    response getAccount(const request&, AuthMiddleware::context&);
    response putMoney(const request&, AuthMiddleware::context&);
    response takeMoney(const request&, AuthMiddleware::context&);
    response transferMoney(const request&, AuthMiddleware::context&);

};
