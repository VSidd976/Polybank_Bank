#include "DepositProductsRepository.h"

DepositProductsRepository::DepositProductsRepository()
    : _db(AppContext::get<Database>()) {}

DepositProductsResponse DepositProductsRepository::findAll() {
    DbTransaction tx(_db);
    auto result = tx.tx().exec(
        R"SQL(
            select id, name, term_months, interest_rate
            from deposit_products
            order by id
        )SQL"
    );

    DepositProductsResponse products;
    for (const auto& row : result) {
        products.depositProducts.push_back({
            row["id"].as<int>(),
            row["name"].as<string>(),
            row["term_months"].as<int>(),
            row["interest_rate"].as<double>()
        });
    }
    return products;
}
