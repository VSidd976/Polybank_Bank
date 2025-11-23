#include "CreditService.h"
#include "AuthMiddleware.h"

CreditService::CreditService() :
    _creditsRepo(AppContext::get<CreditsRepository>()),
    _creditProductsRepo(AppContext::get<CreditProductsRepository>()),
    _accountsRepo(AppContext::get<AccountsRepository>()),
    _operationsRepo(AppContext::get<OperationsRepository>())
{}

CreditProductsResponse CreditService::getCreditProducts() {
    return _creditProductsRepo.findAll();
}

CreditsResponse CreditService::getCredits(AuthMiddleware::context& ctx) {
    return _creditsRepo.findByAccount(ctx.accountId);
}

CreditResponse CreditService::getCredit(AuthMiddleware::context& ctx, int id) {
    auto credit = _creditsRepo.findById(ctx.accountId, id);
    if (!credit.has_value())
        throw runtime_error("credit not found or access denied");
    return credit.value();
}

void CreditService::take(AuthMiddleware::context& ctx, const TakeCreditRequest& dto) {
    auto products = _creditProductsRepo.findAll();
    auto it = find_if(
        products.creditProducts.begin(),
        products.creditProducts.end(),
        [&](const CreditProduct& p) { return p.id == dto.productId; }
    );

    if (it == products.creditProducts.end())
        throw runtime_error("credit product not found");

    if (!_operationsRepo.addCreditTake(ctx.accountId, dto.productId, dto.amount))
        throw runtime_error("failed to take credit");
}

void CreditService::pay(AuthMiddleware::context& ctx, const PayCreditRequest& dto) {
    auto credit = _creditsRepo.findById(ctx.accountId, dto.creditId);
    if (!credit.has_value())
        throw runtime_error("credit not found or access denied");

    if (_accountsRepo.getBalanceById(ctx.accountId) < dto.amount)
        throw runtime_error("insufficient funds");

    if (!_operationsRepo.addCreditPay(ctx.accountId, dto.creditId, dto.amount))
        throw runtime_error("failed to pay credit");
}
