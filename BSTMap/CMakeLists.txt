
project(CPSC223_HW8)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0")
set(CMAKE_BUILD_TYPE Debug)

# locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create unit test executable
add_executable(hw8_test hw8_test.cpp)
target_link_libraries(hw8_test ${GTEST_LIBRARIES} pthread)

# create performance executable
add_executable(hw8_perf hw8_perf.cpp util.cpp)

