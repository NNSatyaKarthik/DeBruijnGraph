cmake_minimum_required(VERSION 3.6)
project(cppCode)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp tests/fizzBuzzTest.cpp src/FizzBuzz.cpp src/FizzBuzz.h src/RabinKarpHash.cpp src/RabinKarpHash.h tests/RabinKarpTest.cpp)
add_executable(cppCode ${SOURCE_FILES})
target_link_libraries(cppCode gtest gtest_main)
