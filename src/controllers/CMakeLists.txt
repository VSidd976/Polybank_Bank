set(CONTROLLERS_SOURCES
        AuthController.cc
        AccountController.cc
        DepositController.cc
)

add_library(controllers STATIC ${CONTROLLERS_SOURCES})

target_link_libraries(controllers PUBLIC Crow requests responses utils services infra filters)
