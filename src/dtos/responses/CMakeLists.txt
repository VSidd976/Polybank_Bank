set(RESPONSES_SOURCES
        VerifyCredentialsResponse.cc
        AccountResponse.cc
        DepositProductsResponse.cc
        DepositResponse.cc
        DepositsResponse.cc
        AutoTransferResponse.cc
        CreditProtectionResponse.cc
        LeftoverRuleResponse.cc
        VerifyCardResponse.cc
        CreditResponse.cc
        CreditsResponse.cc
        CreditProductsResponse.cc
)

add_library(responses STATIC ${RESPONSES_SOURCES})

target_link_libraries(responses PUBLIC Crow nlohmann_json)
