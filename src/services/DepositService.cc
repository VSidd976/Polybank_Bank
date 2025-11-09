#include "DepositService.h"
#include "AuthMiddleware.h"

DepositService::DepositService()
    : _depositsRepo(AppContext::get<DepositsRepository>()),
        _depositProductsRepo(AppContext::get<DepositProductsRepository>()),
        _accountsRepo(AppContext::get<AccountsRepository>())
{}

DepositProductsResponse DepositService::getDepositProducts() {
    return _depositProductsRepo.findAll();
}

DepositsResponse DepositService::getDeposits(AuthMiddleware::context& ctx) {
    return _depositsRepo.findByAccount(ctx._account_id);
}

DepositResponse DepositService::getDeposit(AuthMiddleware::context& ctx, int id) {
    auto deposit = _depositsRepo.findById(ctx._account_id, id);
    if (!deposit.has_value())
        throw runtime_error("deposit not found or access denied");
    return deposit.value();
}

void DepositService::putOn(AuthMiddleware::context& ctx, const OpenDepositRequest& dto) {
    auto products = _depositProductsRepo.findAll();
    auto it = find_if(
        products._depositProducts.begin(),
        products._depositProducts.end(),
        [&](const DepositProduct& p) { return p._id == dto._product_id; }
    );
    if (it == products._depositProducts.end())
        throw runtime_error("deposit product not found");

    if (!_accountsRepo.hasEnoughBalance(ctx._account_id, dto._amount))
        throw runtime_error("insufficient funds");

    if (!_depositsRepo.openDeposit(ctx._account_id, dto._product_id, dto._amount))
        throw runtime_error("failed to open deposit");
}

void DepositService::takeFrom(AuthMiddleware::context& ctx, const CloseDepositRequest& dto) {
    auto dep = _depositsRepo.findById(ctx._account_id, dto._deposit_id);
    if (!dep.has_value())
        throw runtime_error("deposit not found or access denied");

    if (!_depositsRepo.closeDeposit(ctx._account_id, dto._deposit_id))
        throw runtime_error("failed to close deposit");
}
