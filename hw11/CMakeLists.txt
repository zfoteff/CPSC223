cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

#locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#create unit test executable
add_executable(hw11test hw11_tests.cpp)
target_link_libraries(hw11test ${GTEST_LIBRARIES} pthread)

#create performance executable
add_executable(hw11perf hw11_perf.cpp)
