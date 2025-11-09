set(FILTERS_SOURCES
    AuthFilter.cc
    AuthMiddleware.cc
)

add_library(filters STATIC ${FILTERS_SOURCES})

target_link_libraries(filters PUBLIC Crow utils)
