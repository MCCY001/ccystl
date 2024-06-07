cmake_minimum_required(VERSION 3.29)
project(allocator)

set(ALLOCATOR_SRC
    ${ALLOCATOR_DIR}/allocator.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${ALLOCATOR_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${ALLOCATOR_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
