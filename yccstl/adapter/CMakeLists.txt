cmake_minimum_required(VERSION 3.29)
project(adapter)

set(ADAPTER_SRC
    ${ADAPTER_DIR}/adapter.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${ADAPTER_SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${ADAPTER_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_HEADER_DIR}
)
