#include "ClientsRepository.h"

ClientsRepository::ClientsRepository()
    : _db(AppContext::get<Database>())
{}

optional<CardInfo> ClientsRepository::findByCard(const string& card) {
    try {
        pqxx::work tx(_db.getConn());
        auto result = tx.exec(
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

        const auto& row = result[0];
        CardInfo info(
            row["card_id"].as<int>(),
            row["account_id"].as<int>(),
            row["client_id"].as<int>(),
            row["pin"].as<string>()
        );
        return info;
    }
    catch (const exception&) {
        return nullopt;
    }
}
