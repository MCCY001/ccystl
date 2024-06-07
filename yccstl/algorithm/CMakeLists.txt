cmake_minimum_required(VERSION 3.29)
project(algorithm)

set(ALGORITHM_SRC
    ${ALGORITHM_DIR}/algorithm.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${ALGORITHM_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${ALGORITHM_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
