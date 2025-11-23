#pragma once
#include "AppContext.h"
#include "crow.h"
#include "AuthMiddleware.h"
#include "BaseController.h"
#include "DepositService.h"
#include "DepositProductsResponse.h"
#include "OpenDepositRequest.h"
#include "CloseDepositRequest.h"
using namespace std;
using namespace crow;

class DepositController : public BaseController<DepositService> {
public:
    explicit DepositController(App<AuthMiddleware>&);

    void registerRoutes() override;

private:
    response getDepositProducts(const request&);
    response getDeposits(const request&);
    response getDeposit(const request&, int);
    response putOn(const request&);
    response takeFrom(const request&);
};
