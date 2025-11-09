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
            filters
            repositories
            services
            infra
        -Wl,--no-whole-archive
)
