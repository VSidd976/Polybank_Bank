set(SERVICES_SOURCES
        AuthService.cc
        AccountService.cc
        DepositService.cc
)

add_library(services STATIC ${SERVICES_SOURCES})

target_link_libraries(services PUBLIC Crow filters)
