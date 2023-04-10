cmake_minimum_required(VERSION 3.18..3.20)

project(cppdict LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Release
# set(CMAKE_BUILD_TYPE Release)

# test section
message(STATUS "Building tests")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
    cpptest
    test.cpp
)

target_link_libraries(cpptest gtest_main)

target_compile_options(cpptest
    PRIVATE
        -O0
        -Wall
        -g
)

include(GoogleTest)
gtest_discover_tests(cpptest)

find_package(pybind11 REQUIRED)
pybind11_add_module(example bind.cpp)