#pragma once
#include "Database.h"
#include "AppContext.h"

struct CardInfo {
    int _card_id;
    int _account_id;
    int _client_id;
    string _pin;
};

class ClientsRepository {
public:
    explicit ClientsRepository();

    optional<CardInfo> findByCard(const string&);

private:
    Database& _db;

};
