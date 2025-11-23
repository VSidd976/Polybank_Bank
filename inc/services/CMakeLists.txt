target_include_directories(services PUBLIC ./)
target_link_libraries(services PUBLIC Crow repositories infra responses requests utils)
