set(REPOSITORIES_SOURCES
        ClientsRepository.cc
        AccountsRepository.cc
        DepositProductsRepository.cc
        DepositsRepository.cc
        OperationsRepository.cc
)

add_library(repositories STATIC ${REPOSITORIES_SOURCES})

target_link_libraries(repositories PUBLIC Crow infra responses)
