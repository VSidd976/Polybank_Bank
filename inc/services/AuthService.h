#pragma once
#include "ClientsRepository.h"
#include "VerifyCredentialsResponse.h"
#include "VerifyCredentialsRequest.h"
#include "AppContext.h"
#include "JwtUtils.h"

class AuthService {
public:
    explicit AuthService();

    VerifyCredentialsResponse verify(const VerifyCredentialsRequest& dto);
    bool isVerifiedToken(const string& token);

private:
    ClientsRepository& _repo;

};
