cmake_minimum_required(VERSION 3.6)
project(cppCode)

set(CMAKE_CXX_STANDARD 11)
if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})


#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)
#include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/RabinKarpHash.cpp src/RabinKarpHash.h tests/RabinKarpTest.cpp src/ConstructKMers.h tests/ConstructKMersTest.cpp tests/BBHashTest.cpp src/BBHash.h src/GraphDS.cpp src/GraphDS.h tests/GraphDSTest.cpp)
add_executable(cppCode ${SOURCE_FILES})
target_link_libraries(cppCode gtest gtest_main)
