#include "AccountService.h"
#include "AuthMiddleware.h"

AccountService::AccountService()
    : _accountsRepo(AppContext::get<AccountsRepository>()),
        _clientsRepo(AppContext::get<ClientsRepository>()),
        _operationsRepo(AppContext::get<OperationsRepository>())
{}

AccountResponse AccountService::getAccount(AuthMiddleware::context& ctx) {
    auto acc = _accountsRepo.findById(ctx._account_id);
    if (!acc.has_value())
        throw runtime_error("account not found");

    return acc.value();
}

void AccountService::putMoney(const AccountRequest& dto, AuthMiddleware::context& ctx) {
    // auto success = _accountsRepo.changeBalance(ctx._account_id, dto._amount);
    bool success = _operationsRepo.addOperation(nullopt, ctx._account_id, dto._amount, "atm_deposit");
    if (!success)
        throw runtime_error("failed to deposit");
}

void AccountService::takeMoney(const AccountRequest& dto, AuthMiddleware::context& ctx) {
    auto account = _accountsRepo.findById(ctx._account_id);
    if (!account.has_value())
        throw runtime_error("account not found");

    if (account->_balance < dto._amount)
        throw runtime_error("insufficient funds");

    bool success = _operationsRepo.addOperation(ctx._account_id, nullopt, dto._amount, "atm_withdraw");
    // auto success = _accountsRepo.changeBalance(ctx._account_id, -dto._amount);
    if (!success)
        throw runtime_error("failed to withdraw");
}

void AccountService::transferMoney(const TransferMoneyRequest& dto, AuthMiddleware::context& ctx) {
    auto from = _accountsRepo.findById(ctx._account_id);
    auto to = _clientsRepo.findByCard(dto._to);

    if (!from.has_value() || !to.has_value())
        throw runtime_error("account not found");

    if (from->_balance < dto._amount)
        throw runtime_error("insufficient funds");

    bool success = _operationsRepo.addOperation(ctx._account_id, to->_account_id, dto._amount, "transfer");
    // if (!_accountsRepo.transferBalance(ctx._account_id, to->_account_id, dto._amount))
    if (!success)
        throw runtime_error("transfer failed");
}
