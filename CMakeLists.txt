cmake_minimum_required(VERSION 2.8.9)
project(Misja009)

set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall")

add_executable(Misja009 main.cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(SFML COMPONENTS system audio)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML required to compile")
endif()

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries (Misja009 ${SFML_LIBRARIES})
