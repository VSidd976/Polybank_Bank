cmake_minimum_required(VERSION 3.22)

project("Polybank_Bank" VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME "Executable")

add_subdirectory(src)
add_subdirectory(inc)
add_subdirectory(app)
