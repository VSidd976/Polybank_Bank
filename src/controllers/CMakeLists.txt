set(CONTROLLERS_SOURCES
        AuthController.cc
        AccountController.cc
        DepositController.cc
)

add_library(${CONTROLLERS_NAME} STATIC ${CONTROLLERS_SOURCES})

target_link_libraries(${CONTROLLERS_NAME} PUBLIC Crow requests responses utils services infra filters)
