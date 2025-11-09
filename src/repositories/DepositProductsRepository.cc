#include "DepositProductsRepository.h"

DepositProductsRepository::DepositProductsRepository()
    : _db(AppContext::get<Database>()) {}

DepositProductsResponse DepositProductsRepository::findAll() {
    pqxx::work tx(_db.getConn());
    auto res = tx.exec("select id, name, term_months, interest_rate from deposit_products order by id");

    DepositProductsResponse resProducts;
    for (const auto& row : res) {
        resProducts._depositProducts.push_back({
            row["id"].as<int>(),
            row["name"].as<string>(),
            row["term_months"].as<int>(),
            row["interest_rate"].as<double>()
        });
    }
    return resProducts;
}
