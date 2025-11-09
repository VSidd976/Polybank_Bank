#include "AuthService.h"

AuthService::AuthService()
    : _repo(AppContext::get<ClientsRepository>())
{}

VerifyCredentialsResponse AuthService::verify(const VerifyCredentialsRequest& dto) {
    auto cardInfo = _repo.findByCard(dto._card);
    if (!cardInfo.has_value() || cardInfo->_pin != dto._pin)
        throw runtime_error("invalid data");

    auto token = JwtUtils::generateToken(
        cardInfo->_card_id,
        cardInfo->_account_id,
        cardInfo->_client_id
    );

    return VerifyCredentialsResponse(token);
}
