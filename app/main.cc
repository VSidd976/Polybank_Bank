#include <iostream>
#include "JwtUtils.h"
#include "crow.h"
#include "AuthMiddleware.h"
#include "AuthController.h"
#include "AccountController.h"
#include "DepositController.h"
#include "DaemonController.h"
#include "CreditController.h"
#include "AuthService.h"
#include "AccountService.h"
#include "DepositService.h"
#include "DaemonService.h"
#include "CreditService.h"
#include "AccountsRepository.h"
#include "OperationsRepository.h"
#include "DepositsRepository.h"
#include "CardsRepository.h"
#include "CreditsRepository.h"
#include "CreditProductsRepository.h"
#include "DepositProductsRepository.h"
#include "AutoTransfersRepository.h"
#include "LeftoverRulesRepository.h"
#include "CreditProtectionRepository.h"
#include "Database.h"
#include "Config.h"
using namespace crow;
using namespace std;

int main() {
    Config::load(std::string(CMAKE_BINARY_DIR) + "/app/config.json");

    JwtUtils::setSecret(Config::jwtSecret);
    JwtUtils::setExpires(Config::jwtExpire);

    auto app = App<AuthMiddleware>();

    Database db(Config::dbUrl);
    AppContext::add<Database>(db);

    AccountsRepository accountsRepo;
    DepositsRepository depositsRepo;
    DepositProductsRepository depositProductsRepo;
    OperationsRepository operationsRepo;
    AutoTransfersRepository autoTransRepo;
    LeftoverRulesRepository leftoverRulesRepo;
    CreditProtectionRepository creditProtRepo;
    CardsRepository cardsRepo;
    CreditsRepository creditsRepo;
    CreditProductsRepository creditProductsRepo;
    AppContext::add<AccountsRepository>(accountsRepo);
    AppContext::add<DepositsRepository>(depositsRepo);
    AppContext::add<DepositProductsRepository>(depositProductsRepo);
    AppContext::add<OperationsRepository>(operationsRepo);
    AppContext::add<AutoTransfersRepository>(autoTransRepo);
    AppContext::add<LeftoverRulesRepository>(leftoverRulesRepo);
    AppContext::add<CreditProtectionRepository>(creditProtRepo);
    AppContext::add<CardsRepository>(cardsRepo);
    AppContext::add<CreditsRepository>(creditsRepo);
    AppContext::add<CreditProductsRepository>(creditProductsRepo);

    AuthService authServ;
    AccountService accountServ;
    DepositService depositServ;
    DaemonService daemonServ;
    CreditService creditServ;
    AppContext::add<AuthService>(authServ);
    AppContext::add<AccountService>(accountServ);
    AppContext::add<DepositService>(depositServ);
    AppContext::add<DaemonService>(daemonServ);
    AppContext::add<CreditService>(creditServ);

    AuthController authCtrl(app);
    AccountController accountCtrl(app);
    DepositController depositCtrl(app);
    DaemonController daemonCtrl(app);
    CreditController creditCtrl(app);
    authCtrl.registerRoutes();
    accountCtrl.registerRoutes();
    depositCtrl.registerRoutes();
    daemonCtrl.registerRoutes();
    creditCtrl.registerRoutes();

    CROW_ROUTE(app, "/api/docs")
    ([](){
        response res;
        res.code = 302;
        res.add_header("Location", "/static/index.html");
        return res;
    });

    app.port(18973).run();

    return 0;
}
