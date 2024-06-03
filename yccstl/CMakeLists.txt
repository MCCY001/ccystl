cmake_minimum_required(VERSION 3.29)
project(yccstl)

set(TEST_MODULE_DIR ${MAIN_PROJECT_DIR}/test_module)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    test_module
)

add_subdirectory(${TEST_MODULE_DIR})