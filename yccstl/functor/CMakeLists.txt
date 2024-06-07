cmake_minimum_required(VERSION 3.29)
project(functor)

set(FUNCTOR_SRC
    ${FUNCTOR_DIR}/functor.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${FUNCTOR_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${FUNCTOR_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
