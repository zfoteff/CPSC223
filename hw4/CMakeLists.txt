cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

#locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#create unit test executable
add_executable(hw4test hw4_tests.cpp)
target_link_libraries(hw4test ${GTEST_LIBRARIES} pthread)

#create performance add_executable
add_executable(hw4perf hw4_perf.cpp)
