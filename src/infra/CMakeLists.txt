set(INFRA_SOURCES
    DbTransaction.cc
    Database.cc
    Config.cc
)

add_library(infra STATIC ${INFRA_SOURCES})

target_link_libraries(infra PUBLIC Crow pqxx nlohmann_json)
