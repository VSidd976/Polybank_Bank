#pragma once
#include "CreditsRepository.h"
#include "CreditProductsRepository.h"
#include "OperationsRepository.h"
#include "AccountsRepository.h"
#include "CreditResponse.h"
#include "CreditsResponse.h"
#include "CreditProductsResponse.h"
#include "PayCreditRequest.h"
#include "TakeCreditRequest.h"
#include "AuthMiddleware.h"
#include "AppContext.h"

class CreditService {
public:
    explicit CreditService();

    CreditProductsResponse getCreditProducts();
    CreditsResponse getCredits(AuthMiddleware::context&);
    CreditResponse getCredit(AuthMiddleware::context&, int);
    void pay(AuthMiddleware::context&, const PayCreditRequest&);
    void take(AuthMiddleware::context&, const TakeCreditRequest&);

private:
    CreditsRepository& _creditsRepo;
    CreditProductsRepository& _creditProductsRepo;
    AccountsRepository& _accountsRepo;
    OperationsRepository& _operationsRepo;
};
