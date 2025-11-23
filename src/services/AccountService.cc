#include "AccountService.h"
#include "AuthMiddleware.h"

AccountService::AccountService() :
    _accountsRepo(AppContext::get<AccountsRepository>()),
    _cardsRepo(AppContext::get<CardsRepository>()),
    _operationsRepo(AppContext::get<OperationsRepository>())
{}

AccountResponse AccountService::getAccount(AuthMiddleware::context& ctx) {
    auto acc = _accountsRepo.findById(ctx.accountId);
    if (!acc.has_value()) throw runtime_error("account not found");
    return acc.value();
}

void AccountService::putMoney(const AccountRequest& dto, AuthMiddleware::context& ctx) {
    bool success = _operationsRepo.addAtmDeposit(ctx.accountId, dto.amount);
    if (!success) throw runtime_error("failed to deposit");
}

void AccountService::takeMoney(const AccountRequest& dto, AuthMiddleware::context& ctx) {
    auto account = _accountsRepo.findById(ctx.accountId);
    if (!account.has_value())
        throw runtime_error("account not found");

    if (account->balance < dto.amount)
        throw runtime_error("insufficient funds");

    bool success = _operationsRepo.addAtmWithdraw(ctx.accountId, dto.amount);
    if (!success) throw runtime_error("failed to withdraw");
}

void AccountService::transferMoney(const TransferMoneyRequest& dto, AuthMiddleware::context& ctx) {
    auto from = _accountsRepo.findById(ctx.accountId);
    auto to = _cardsRepo.findByCard(dto.to);

    if (!from.has_value() || !to.has_value())
        throw runtime_error("account not found");

    if (from->balance < dto.amount)
        throw runtime_error("insufficient funds");

    bool success = _operationsRepo.addTransfer(ctx.accountId, to->accountId, dto.amount);
    if (!success)
        throw runtime_error("transfer failed");
}
