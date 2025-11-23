set(UTILS_SOURCES
        JwtUtils.cc
)

add_library(utils STATIC ${UTILS_SOURCES})

target_link_libraries(utils PUBLIC Crow)
