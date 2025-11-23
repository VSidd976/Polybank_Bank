#pragma once
#include "CardsRepository.h"
#include "VerifyCredentialsResponse.h"
#include "VerifyCredentialsRequest.h"
#include "VerifyCardResponse.h"
#include "VerifyCardRequest.h"
#include "AppContext.h"
#include "JwtUtils.h"

class AuthService {
public:
    explicit AuthService();

    VerifyCredentialsResponse verifyCredentials(const VerifyCredentialsRequest&);
    VerifyCardResponse verifyCard(const VerifyCardRequest&);
    bool isVerifiedToken(const string&);

private:
    CardsRepository& _cardsRepo;
};
