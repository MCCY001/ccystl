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
    ${ITERATOR_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${MAIN_PROJECT_DIR}
    ${ALLOCATOR_DIR}
    ${EXTERNAL_HEADER_DIR}
)
