cmake_minimum_required(VERSION 3.11)
project(cache_lfu)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(lfu cache_lfu.cpp)
target_include_directories(lfu PUBLIC ${INCLUDE_DIR})

add_executable(belady cache_belady.cpp)
target_include_directories(belady PUBLIC ${INCLUDE_DIR})