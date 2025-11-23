set(REPOSITORIES_SOURCES
        AccountsRepository.cc
        DepositProductsRepository.cc
        DepositsRepository.cc
        OperationsRepository.cc
        AutoTransfersRepository.cc
        CreditProtectionRepository.cc
        LeftoverRulesRepository.cc
        CardsRepository.cc
        CreditProductsRepository.cc
        CreditsRepository.cc
)

add_library(repositories STATIC ${REPOSITORIES_SOURCES})

target_link_libraries(repositories PUBLIC Crow infra responses)
