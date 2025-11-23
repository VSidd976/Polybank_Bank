#pragma once
#include "CreditProtectionRepository.h"
#include "LeftoverRulesRepository.h"
#include "CardsRepository.h"
#include "CreateCreditProtectionRequest.h"
#include "CreateLeftoverRuleRequest.h"
#include "CreateAutoTransferRequest.h"
#include "AutoTransferResponse.h"
#include "LeftoverRuleResponse.h"
#include "CreditProtectionResponse.h"
#include "AutoTransfersRepository.h"
#include "AuthMiddleware.h"
#include "AppContext.h"
#include "JwtUtils.h"

class DaemonService {
public:
    explicit DaemonService();

    void createCreditProtection(const CreateCreditProtectionRequest&, AuthMiddleware::context&);
    void createLeftover(const CreateLeftoverRuleRequest&, AuthMiddleware::context&);
    void createAutoTransfer(const CreateAutoTransferRequest&, AuthMiddleware::context&);

    vector<AutoTransferResponse> getAutoTransfers(AuthMiddleware::context&);
    vector<LeftoverRuleResponse> getLeftovers(AuthMiddleware::context&);
    vector<CreditProtectionResponse> getCreditProtections(AuthMiddleware::context&);

    void deleteAutoTransfer(AuthMiddleware::context&, int);
    void deleteLeftover(AuthMiddleware::context&, int);
    void deleteCreditProtection(AuthMiddleware::context&, int);

private:
    CreditProtectionRepository& _creditProtRepo;
    LeftoverRulesRepository& _leftoverRepo;
    AutoTransfersRepository& _autoTransRepo;
    CardsRepository& _cardsRepo;
};
