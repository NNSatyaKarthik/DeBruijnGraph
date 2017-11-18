cmake_minimum_required(VERSION 3.6)
project(cppCode)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/RabinKarpHash.cpp src/RabinKarpHash.h tests/RabinKarpTest.cpp src/ConstructKMers.h tests/ConstructKMersTest.cpp tests/BBHashTest.cpp src/BBHash.h src/GraphDS.cpp src/GraphDS.h)
add_executable(cppCode ${SOURCE_FILES})
target_link_libraries(cppCode gtest gtest_main)
