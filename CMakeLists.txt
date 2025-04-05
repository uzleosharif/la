


cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_FLAGS "-stdlib=libc++")

project(la CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_MODULE_STD ON)



add_library(la SHARED)
target_compile_features(la PRIVATE cxx_std_26)
target_sources(la PUBLIC
  FILE_SET moduels TYPE CXX_MODULES
    FILES la.cppm
)

add_executable(test)
target_sources(test PRIVATE main.cpp)
target_link_libraries(test PRIVATE la)
target_compile_features(test PRIVATE cxx_std_26)
target_compile_options(test PRIVATE -fsanitize=address -Wall -Wextra -Wpedantic)
target_link_options(test PRIVATE -fsanitize=address)
