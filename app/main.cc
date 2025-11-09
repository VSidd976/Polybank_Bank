#include <iostream>
#include "JwtUtils.h"
#include "crow.h"
#include "AuthMiddleware.h"
#include "AuthController.h"
#include "AccountController.h"
#include "DepositController.h"
#include "AuthService.h"
#include "AccountService.h"
#include "DepositService.h"
#include "ClientsRepository.h"
#include "AccountsRepository.h"
#include "OperationsRepository.h"
#include "DepositsRepository.h"
#include "DepositProductsRepository.h"
#include "Database.h"
using namespace crow;
using namespace std;

string JwtUtils::_secretKey = "dsdsd1";
int JwtUtils::_expiresSec = 300;

int main() {
    auto app = App<AuthMiddleware>();

    Database db("postgresql://postgres:abc123@16.170.29.95:15864/polybank");
    AppContext::add<Database>(db);

    ClientsRepository clientsRepo;
    AccountsRepository accountsRepo;
    DepositsRepository depositsRepo;
    DepositProductsRepository depositProductsRepo;
    OperationsRepository operationsRepo;
    AppContext::add<ClientsRepository>(clientsRepo);
    AppContext::add<AccountsRepository>(accountsRepo);
    AppContext::add<DepositsRepository>(depositsRepo);
    AppContext::add<DepositProductsRepository>(depositProductsRepo);
    AppContext::add<OperationsRepository>(operationsRepo);

    AuthService authServ;
    AccountService accountServ;
    DepositService depositServ;
    AppContext::add<AuthService>(authServ);
    AppContext::add<AccountService>(accountServ);
    AppContext::add<DepositService>(depositServ);

    AuthController authCtrl(app);
    AccountController accountCtrl(app);
    DepositController depositCtrl(app);
    authCtrl.registerRoutes();
    accountCtrl.registerRoutes();
    depositCtrl.registerRoutes();

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18973).run();

    return 0;
}
