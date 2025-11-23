#pragma once
#include "DbTransaction.h"
#include "AppContext.h"
#include "CardResponse.h"

class CardsRepository {
public:
    explicit CardsRepository();

    bool exists(const string&);
    optional<int> findAccountIdByCard(const string&);
    optional<CardResponse> findByCard(const string&);

private:
    Database& _db;
};
