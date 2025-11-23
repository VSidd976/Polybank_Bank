set(MIDDLEWARES_SOURCES
    AuthMiddleware.cc
)

add_library(middlewares STATIC ${MIDDLEWARES_SOURCES})

target_link_libraries(middlewares PUBLIC Crow utils)
