cmake_minimum_required(VERSION 3.14)
project(nas-nr VERSION 16.1.0 DESCRIPTION "Routines for NAS-NR(5GS)")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

include_directories(PRIVATE ${PROJECT_SOURCE_DIR/}/nas-nr/comm
        ${PROJECT_SOURCE_DIR/}/nas-nr/sm
        ${PROJECT_SOURCE_DIR/}/nas-nr/mm nas-nr)

add_subdirectory(nas-nr)
add_subdirectory(demo)