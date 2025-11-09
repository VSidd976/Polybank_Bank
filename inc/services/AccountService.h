#pragma once
#include "AccountsRepository.h"
#include "AccountRequest.h"
#include "AccountResponse.h"
#include "TransferMoneyRequest.h"
#include "VerifyCredentialsResponse.h"
#include "VerifyCredentialsRequest.h"
#include "AppContext.h"
#include "JwtUtils.h"
#include "AuthMiddleware.h"
#include "ClientsRepository.h"
#include "OperationsRepository.h"

class AccountService {
public:
    explicit AccountService();

    AccountResponse getAccount(AuthMiddleware::context&);
    void putMoney(const AccountRequest&, AuthMiddleware::context& ctx);
    void takeMoney(const AccountRequest&, AuthMiddleware::context& ctx);
    void transferMoney(const TransferMoneyRequest&, AuthMiddleware::context& ctx);

private:
    AccountsRepository& _accountsRepo;
    ClientsRepository& _clientsRepo;
    OperationsRepository& _operationsRepo;
};
