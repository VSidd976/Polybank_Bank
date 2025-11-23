#pragma once
#include "DepositsRepository.h"
#include "OperationsRepository.h"
#include "DepositResponse.h"
#include "DepositsResponse.h"
#include "DepositProductsResponse.h"
#include "DepositProductsRepository.h"
#include "CloseDepositRequest.h"
#include "AccountsRepository.h"
#include "OpenDepositRequest.h"
#include "AuthMiddleware.h"
#include "AppContext.h"

class DepositService {
public:
    explicit DepositService();

    DepositProductsResponse getDepositProducts();
    DepositsResponse getDeposits(AuthMiddleware::context&);
    DepositResponse getDeposit(AuthMiddleware::context&, int);
    void putOn(AuthMiddleware::context&, const OpenDepositRequest&);
    void takeFrom(AuthMiddleware::context&, const CloseDepositRequest&);

private:
    DepositsRepository& _depositsRepo;
    DepositProductsRepository& _depositProductsRepo;
    AccountsRepository& _accountsRepo;
    OperationsRepository& _operationsRepo;
};
