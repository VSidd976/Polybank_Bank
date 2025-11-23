#include "AuthService.h"

AuthService::AuthService()
    : _cardsRepo(AppContext::get<CardsRepository>())
{}

VerifyCredentialsResponse AuthService::verifyCredentials(const VerifyCredentialsRequest& dto) {
    auto cardRes = _cardsRepo.findByCard(dto.card);
    if (!cardRes.has_value() || cardRes->pin != dto.pin)
        throw runtime_error("invalid data");

    auto token = JwtUtils::generateToken(
        cardRes->cardId,
        cardRes->accountId,
        cardRes->clientId
    );

    return VerifyCredentialsResponse(token);
}

VerifyCardResponse AuthService::verifyCard(const VerifyCardRequest& dto) {
    return VerifyCardResponse(_cardsRepo.exists(dto.card));
}
