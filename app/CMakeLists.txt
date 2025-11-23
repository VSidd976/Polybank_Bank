add_executable(${EXECUTABLE_NAME} main.cc)

target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
        Crow
        nlohmann_json
        -Wl,--whole-archive
            controllers
            requests
            responses
            utils
            middlewares
            repositories
            services
            infra
        -Wl,--no-whole-archive
)

add_custom_command(
    TARGET Executable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/config.json
            ${CMAKE_BINARY_DIR}/app/config.json
)

add_custom_command(
    TARGET Executable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/static
            ${CMAKE_BINARY_DIR}/app/static
)
