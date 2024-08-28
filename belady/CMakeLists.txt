cmake_minimum_required(VERSION 3.11)
project(cache_belady)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(belady cache_belady.cpp)
target_include_directories(belady PUBLIC ${INCLUDE_DIR})