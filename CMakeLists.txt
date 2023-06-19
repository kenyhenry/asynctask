cmake_minimum_required(VERSION 3.18)

project(taskmanager)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX ./bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(ENABLE_TEST OFF)

include_directories(./include)

file(GLOB_RECURSE HDRS ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${HDRS})

########
# TEST #
########
if(ENABLE_TEST)
    file(GLOB_RECURSE SRCSTEST ${PROJECT_SOURCE_DIR}/test/*.cpp)
    file(GLOB_RECURSE HDRSTEST ${PROJECT_SOURCE_DIR}/test/*.hpp)

    add_executable(${PROJECT_NAME}_test ${SRCSTEST} ${HDRSTEST} ./test/main.cpp)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE taskmanager)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE pthread)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE uuid)
    
endif()