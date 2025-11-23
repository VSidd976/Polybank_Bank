#include "DaemonService.h"

DaemonService::DaemonService() :
    _creditProtRepo(AppContext::get<CreditProtectionRepository>()),
    _leftoverRepo(AppContext::get<LeftoverRulesRepository>()),
    _autoTransRepo(AppContext::get<AutoTransfersRepository>()),
    _cardsRepo(AppContext::get<CardsRepository>())
{}

void DaemonService::createCreditProtection(const CreateCreditProtectionRequest& dto, AuthMiddleware::context& ctx) {
    auto accIdOpt = _cardsRepo.findAccountIdByCard(dto.backupCard);
    if (!accIdOpt.has_value())
        throw runtime_error("backup card not found");

    if (ctx.accountId == accIdOpt.value())
        throw runtime_error("backup account must be different");

    if (!_creditProtRepo.createRule(ctx.accountId, accIdOpt.value(), dto.minBalance))
        throw runtime_error("failed to create rule");
}

void DaemonService::createLeftover(const CreateLeftoverRuleRequest& dto, AuthMiddleware::context& ctx) {
    auto trgIdOpt = _cardsRepo.findAccountIdByCard(dto.trgCard);
    if (!trgIdOpt.has_value())
        throw runtime_error("target card not found");

    if (ctx.accountId == trgIdOpt.value())
        throw runtime_error("cannot transfer to same account");

    if (!_leftoverRepo.createRule(ctx.accountId, trgIdOpt.value(), dto.threshold))
        throw runtime_error("failed to create leftover rule");
}

void DaemonService::createAutoTransfer(const CreateAutoTransferRequest& dto, AuthMiddleware::context& ctx) {
    auto trgIdOpt = _cardsRepo.findAccountIdByCard(dto.trgCard);
    if (!trgIdOpt.has_value())
        throw runtime_error("target card not found");

    if (ctx.accountId == trgIdOpt.value())
        throw runtime_error("cannot transfer to same account");

    if (!_autoTransRepo.createRule(
            ctx.accountId, trgIdOpt.value(), dto.amount,
            dto.periodicity, dto.nextRunDate))
        throw runtime_error("failed to create auto transfer");
}

vector<AutoTransferResponse> DaemonService::getAutoTransfers(AuthMiddleware::context& ctx) {
    return _autoTransRepo.findByAccount(ctx.accountId);
}

vector<LeftoverRuleResponse> DaemonService::getLeftovers(AuthMiddleware::context& ctx) {
    return _leftoverRepo.findByAccount(ctx.accountId);
}

vector<CreditProtectionResponse> DaemonService::getCreditProtections(AuthMiddleware::context& ctx) {
    return _creditProtRepo.findByAccount(ctx.accountId);
}

void DaemonService::deleteAutoTransfer(AuthMiddleware::context& ctx, int id) {
    if (!_autoTransRepo.disableRule(id, ctx.accountId))
        throw runtime_error("failed to delete auto transfer");
}

void DaemonService::deleteLeftover(AuthMiddleware::context& ctx, int id) {
    if (!_leftoverRepo.disableRule(id, ctx.accountId))
        throw runtime_error("failed to delete leftover rule");
}

void DaemonService::deleteCreditProtection(AuthMiddleware::context& ctx, int id) {
    if (!_creditProtRepo.disableRule(id, ctx.accountId))
        throw runtime_error("failed to delete credit protection rule");
}
