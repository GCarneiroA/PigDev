

add_executable(example01 main.cpp)

target_link_libraries(example01 PUBLIC Pig)

target_include_directories(example01 PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src")
