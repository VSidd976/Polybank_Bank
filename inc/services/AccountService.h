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
#include "OperationsRepository.h"
#include "CardsRepository.h"

class AccountService {
public:
    explicit AccountService();

    AccountResponse getAccount(AuthMiddleware::context&);
    void putMoney(const AccountRequest&, AuthMiddleware::context&);
    void takeMoney(const AccountRequest&, AuthMiddleware::context&);
    void transferMoney(const TransferMoneyRequest&, AuthMiddleware::context&);

private:
    AccountsRepository& _accountsRepo;
    CardsRepository& _cardsRepo;
    OperationsRepository& _operationsRepo;
};
