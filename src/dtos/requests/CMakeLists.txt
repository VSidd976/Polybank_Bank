set(REQUESTS_SOURCES
        VerifyCredentialsRequest.cc
        AccountRequest.cc
        TransferMoneyRequest.cc
        OpenDepositRequest.cc
        CloseDepositRequest.cc
)

add_library(requests STATIC ${REQUESTS_SOURCES})

target_link_libraries(requests PUBLIC Crow nlohmann_json)
