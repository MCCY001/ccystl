cmake_minimum_required(VERSION 3.29)
project(iterator)

set(ITERATOR_SRC
    ${ITERATOR_DIR}/iterator.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${ITERATOR_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${ITERATOR_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
