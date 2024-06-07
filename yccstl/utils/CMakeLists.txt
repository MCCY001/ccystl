cmake_minimum_required(VERSION 3.29)
project(utils)

set(UTILS_SRC
    ${UTILS_DIR}/utils.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${UTILS_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${UTILS_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
