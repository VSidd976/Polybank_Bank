set(SERVICES_SOURCES
        AuthService.cc
        AccountService.cc
        DepositService.cc
        DaemonService.cc
        CreditService.cc
)

add_library(services STATIC ${SERVICES_SOURCES})

target_link_libraries(services PUBLIC Crow middlewares)
