#include "DepositService.h"
#include "AuthMiddleware.h"

DepositService::DepositService() :
    _depositsRepo(AppContext::get<DepositsRepository>()),
    _depositProductsRepo(AppContext::get<DepositProductsRepository>()),
    _accountsRepo(AppContext::get<AccountsRepository>()),
    _operationsRepo(AppContext::get<OperationsRepository>())
{}

DepositProductsResponse DepositService::getDepositProducts() {
    return _depositProductsRepo.findAll();
}

DepositsResponse DepositService::getDeposits(AuthMiddleware::context& ctx) {
    return _depositsRepo.findByAccount(ctx.accountId);
}

DepositResponse DepositService::getDeposit(AuthMiddleware::context& ctx, int id) {
    auto deposit = _depositsRepo.findById(ctx.accountId, id);
    if (!deposit.has_value())
        throw runtime_error("deposit not found or access denied");
    return deposit.value();
}

void DepositService::putOn(AuthMiddleware::context& ctx, const OpenDepositRequest& dto) {
    auto products = _depositProductsRepo.findAll();
    auto it = find_if(
        products.depositProducts.begin(),
        products.depositProducts.end(),
        [&](const DepositProduct& p) { return p.id == dto.productId; }
    );
    if (it == products.depositProducts.end())
        throw runtime_error("deposit product not found");

    if (_accountsRepo.getBalanceById(ctx.accountId) < dto.amount)
        throw runtime_error("insufficient funds");

    if (!_operationsRepo.addDepositOpen(ctx.accountId, dto.productId, dto.amount))
        throw runtime_error("failed to open deposit");
}

void DepositService::takeFrom(AuthMiddleware::context& ctx, const CloseDepositRequest& dto) {
    auto dep = _depositsRepo.findById(ctx.accountId, dto.depositId);
    if (!dep.has_value())
        throw runtime_error("deposit not found or access denied");

    if (!_operationsRepo.addDepositClose(ctx.accountId, dto.depositId))
        throw runtime_error("failed to close deposit");
}
