cmake_minimum_required(VERSION 3.22)

project("Polybank_Bank" VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME "Executable")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CPM)

CPMAddPackage(
    NAME jwt-cpp
    GITHUB_REPOSITORY Thalhammer/jwt-cpp
    VERSION 0.7.1
)
CPMAddPackage(
    NAME Crow
    GITHUB_REPOSITORY CrowCpp/Crow
    VERSION 1.3.0
)
CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.12.0
)
CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx
    GIT_TAG 7.10.1
)

add_subdirectory(src)
add_subdirectory(inc)
add_subdirectory(app)
