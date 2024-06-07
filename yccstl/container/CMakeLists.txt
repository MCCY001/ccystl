cmake_minimum_required(VERSION 3.29)
project(container)

set(CONTAINER_SRC
    ${CONTAINER_DIR}/container.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${CONTAINER_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CONTAINER_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
