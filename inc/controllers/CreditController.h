#pragma once
#include "AppContext.h"
#include "crow.h"
#include "CreditProductsResponse.h"
#include "CreditResponse.h"
#include "CreditsResponse.h"
#include "PayCreditRequest.h"
#include "TakeCreditRequest.h"
#include "AuthMiddleware.h"
#include "BaseController.h"
#include "CreditService.h"
using namespace std;
using namespace crow;

class CreditController : public BaseController<CreditService> {
public:
    explicit CreditController(App<AuthMiddleware>&);

    void registerRoutes() override;

private:
    response getCreditProducts(const request&);
    response getCredits(const request&);
    response getCredit(const request&, int);
    response pay(const request&);
    response take(const request&);
};
