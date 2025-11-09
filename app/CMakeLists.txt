add_executable(${EXECUTABLE_NAME} main.cc)

target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
        Crow
        nlohmann_json
        -Wl,--whole-archive
            ${CONTROLLERS_NAME}
            requests
            responses
            utils
            filters
            repositories
            services
            infra
        -Wl,--no-whole-archive
)

# configure_file(
#         ${CMAKE_SOURCE_DIR}/config.json
#         ${CMAKE_CURRENT_BINARY_DIR}/config.json
#         COPYONLY
# )
