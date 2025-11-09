set(INFRA_SOURCES
    # AppContext.cc
    Database.cc
)

add_library(infra STATIC ${INFRA_SOURCES})

target_link_libraries(infra PUBLIC Crow pqxx)
