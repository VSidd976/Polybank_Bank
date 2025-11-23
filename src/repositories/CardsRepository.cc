#include "CardsRepository.h"

CardsRepository::CardsRepository()
    : _db(AppContext::get<Database>())
{}

bool CardsRepository::exists(const string& card) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select 1 from cards where card = $1 limit 1
        )SQL",
        pqxx::params(card)
    );

    return !result.empty();
}

optional<int> CardsRepository::findAccountIdByCard(const string& card) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select a.id
            from cards c
            join accounts a on c.account_id = a.id
            where c.card = $1
            limit 1
        )SQL",
        pqxx::params(card)
    );

    if (result.empty()) return nullopt;
    return result[0]["id"].as<int>();
}

optional<CardResponse> CardsRepository::findByCard(const string& card) {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select c.id as card_id, c.pin, a.id as account_id, cl.id as client_id
            from cards c
            join accounts a on c.account_id = a.id
            join clients cl on a.client_id = cl.id
            where c.card = $1
        )SQL",
        pqxx::params(card)
    );

    if (result.empty()) return nullopt;
    CardResponse res(
        result[0]["card_id"].as<int>(),
        result[0]["account_id"].as<int>(),
        result[0]["client_id"].as<int>(),
        result[0]["pin"].as<string>()
    );
    return res;
}
