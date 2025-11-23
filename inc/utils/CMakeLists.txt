target_include_directories(utils PUBLIC ./)
target_link_libraries(utils PUBLIC Crow jwt-cpp nlohmann_json)
# target_link_libraries(utils PUBLIC jwt-cpp)
