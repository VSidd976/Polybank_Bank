#pragma once
#include "DaemonService.h"
#include "BaseController.h"
#include "AuthMiddleware.h"
#include "AppContext.h"
#include "JsonUtils.h"
#include "CreateCreditProtectionRequest.h"
#include "CreateAutoTransferRequest.h"
#include "crow.h"
using namespace std;
using namespace crow;

class DaemonController : public BaseController<DaemonService> {
public:
    explicit DaemonController(App<AuthMiddleware>&);

    void registerRoutes() override;

private:
    response createCreditProtection(const request&);
    response getCreditProtections(const request&);
    response deleteCreditProtection(const request&, int);

    response createLeftover(const request&);
    response getLeftovers(const request&);
    response deleteLeftover(const request&, int);

    response createAutoTransfer(const request&);
    response getAutoTransfers(const request&);
    response deleteAutoTransfer(const request&, int);
};
