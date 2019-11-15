cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

#locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#create unit test executable
add_executable(hw9test hw9_tests.cpp)
target_link_libraries(hw8test ${GTEST_LIBRARIES} pthread)

#create performance add_executable
add_executable(hw9perf hw9_perf.cpp)
