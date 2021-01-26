cmake_minimum_required(VERSION 3.0)

project(kangaroo)

set(CXX_FLAGS
 -O2
 -g
 -Wall
 -Wextra
 -Werror
 -std=c++14
 -pthread
)

# ---[ Flags
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# ---[ Includes
# include directories
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src/util
  /usr/local/include
  /usr/include
)

# --[ Output directory
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(
  ${PROJECT_BINARY_DIR}/libs

  /usr/local/lib
  /use/lib
)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

# ---[ Subdirectories
add_subdirectory(src)
add_subdirectory(test)


message(STATUS "CMAKE_CXX_FLAGS=" "${CMAKE_CXX_FLAGS}")

message(STATUS "PROJECT_BINARY_DIR=" "${PROJECT_BINARY_DIR}")

message(STATUS "PROJECT_SOURCE_DIR=" "${PROJECT_SOURCE_DIR}")

message(STATUS "CMAKE_BINARY_DIR=" "${CMAKE_BINARY_DIR}")