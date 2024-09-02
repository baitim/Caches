cmake_minimum_required(VERSION 3.11)
project(caches)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -fsanitize=address -fsanitize=undefined")

add_subdirectory(./lfu)
add_subdirectory(./belady)