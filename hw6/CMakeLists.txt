
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

#locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#create unit test executable
add_executable(hw6test hw6_tests.cpp)
target_link_libraries(hw6test ${GTEST_LIBRARIES} pthread)

# create sort performance executable
add_executable(hw6sort hw6_sort.cpp)
