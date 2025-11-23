#include "JwtUtils.h"

string JwtUtils::_secretKey = "";
int JwtUtils::_expiresSec = 300;

void JwtUtils::setSecret(const string& secret) {
    _secretKey = secret;
}

void JwtUtils::setExpires(int sec) {
    _expiresSec = sec;
}

string JwtUtils::generateToken(const int cardId, const int accountId, const int clientId) {
    auto token = jwt::create()
        .set_issuer("polybank")
        .set_type("JWS")
        .set_payload_claim("card_id", jwt::claim(to_string(cardId)))
        .set_payload_claim("account_id", jwt::claim(to_string(accountId)))
        .set_payload_claim("client_id", jwt::claim(to_string(clientId)))
        .set_issued_at(chrono::system_clock::now())
        .set_expires_at(chrono::system_clock::now() + chrono::seconds(_expiresSec))
        .sign(jwt::algorithm::hs256(_secretKey));
    return token;
}

bool JwtUtils::verifyToken(const string& token, int& cardId, int& accountId, int& clientId) {
    try {
        auto decoded = jwt::decode(token);
        jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256(_secretKey))
            .with_issuer("polybank")
            .verify(decoded);

        cardId = stoi(decoded.get_payload_claim("card_id").as_string());
        accountId = stoi(decoded.get_payload_claim("account_id").as_string());
        clientId = stoi(decoded.get_payload_claim("client_id").as_string());

        return true;
    } catch(const exception& ex) {
        return false;
    }
}
