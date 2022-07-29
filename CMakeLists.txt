cmake_minimum_required(VERSION 3.18)

project(chronotask)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./include)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HDRS ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} main.cpp)