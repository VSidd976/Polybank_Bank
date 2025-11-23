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
    response getAccount(const request&);
    response putMoney(const request&);
    response takeMoney(const request&);
    response transferMoney(const request&);
};
