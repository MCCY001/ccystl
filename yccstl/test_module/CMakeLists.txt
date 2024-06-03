cmake_minimum_required(VERSION 3.29)
project(test_module)

set(TEST_MODULE_SRC
    ${TEST_MODULE_DIR}/test_module.cpp
    ${TEST_MODULE_DIR}/calculation/add.cpp
    ${TEST_MODULE_DIR}/calculation/mult.cpp
)

add_library(${PROJECT_NAME} STATIC ${TEST_MODULE_SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)

# target_include_directories(${PROJECT_NAME}
# PRIVATE
# ${TEST_MODULE_DIR}
# )