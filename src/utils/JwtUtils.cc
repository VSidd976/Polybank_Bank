#include "JwtUtils.h"

string JwtUtils::generateToken(const int card_id, const int account_id, const int client_id) {
    auto token = jwt::create()
        .set_issuer("polybank")
        .set_type("JWS")
        .set_payload_claim("card_id", jwt::claim(to_string(card_id)))
        .set_payload_claim("account_id", jwt::claim(to_string(account_id)))
        .set_payload_claim("client_id", jwt::claim(to_string(client_id)))
        .set_issued_at(chrono::system_clock::now())
        .set_expires_at(chrono::system_clock::now() + chrono::seconds(_expiresSec))
        .sign(jwt::algorithm::hs256(_secretKey));
    return token;
}

bool JwtUtils::verifyToken(const string& token, int& card_id, int& account_id, int& client_id) {
    try {
        auto decoded = jwt::decode(token);
        jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256(_secretKey))
            .with_issuer("polybank")
            .verify(decoded);

        card_id = stoi(decoded.get_payload_claim("card_id").as_string());
        account_id = stoi(decoded.get_payload_claim("account_id").as_string());
        client_id = stoi(decoded.get_payload_claim("client_id").as_string());

        return true;
    } catch(const exception& ex) {
        return false;
    }
}
