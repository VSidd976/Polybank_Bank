#include "CreditProductsRepository.h"

CreditProductsRepository::CreditProductsRepository()
    : _db(AppContext::get<Database>()) {}

CreditProductsResponse CreditProductsRepository::findAll() {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select id, name, term_months, interest_rate
            from credit_products
            order by id
        )SQL"
    );

    CreditProductsResponse products;
    for (const auto& row : result) {
        products.creditProducts.push_back({
            row["id"].as<int>(),
            row["name"].as<string>(),
            row["term_months"].as<int>(),
            row["interest_rate"].as<double>()
        });
    }
    return products;
}
