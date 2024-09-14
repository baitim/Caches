cmake_minimum_required(VERSION 3.11)
project(src)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(lfu cache_lfu.cpp)
target_include_directories(lfu PUBLIC ${INCLUDE_DIR})

add_executable(belady cache_belady.cpp)
target_include_directories(belady PUBLIC ${INCLUDE_DIR})

add_executable(arc cache_arc.cpp)
target_include_directories(arc PUBLIC ${INCLUDE_DIR})

set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/tests/run_tests.py")
add_test(
    NAME caches_tests
    COMMAND python3 ${PYTHON_SCRIPT}
)