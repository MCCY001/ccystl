cmake_minimum_required(VERSION 3.29)
project(ccystl_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main_test.cpp
        ../ccystl/adapter/priority_queue.h
        ../ccystl/adapter/queue.h
        ../ccystl/adapter/stack.h
        ../ccystl/algorithm/algorithm.h
        ../ccystl/container/associative_container/map.h
        ../ccystl/container/associative_container/multimap.h
        ../ccystl/container/associative_container/multiset.h
        ../ccystl/container/associative_container/set.h
        ../ccystl/utils/except_def.h
        ../ccystl/container/sequence_container/array.h
        ../ccystl/container/sequence_container/astring.h
        ../ccystl/container/sequence_container/list.h
        ../ccystl/container/sequence_container/forward_list.h
        ../ccystl/container/unordered_container/unordered_map.h
        ../ccystl/container/unordered_container/unordered_multimap.h
        ../ccystl/container/unordered_container/unordered_multiset.h
        ../ccystl/container/unordered_container/unordered_set.h
        ../ccystl/internal/node.h)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
)