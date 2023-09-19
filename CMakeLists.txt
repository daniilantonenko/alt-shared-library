# Checking the CMake
cmake_minimum_required(VERSION 3.14) 

# Project name and availability check C++ compiler
project(PLcomparer VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

# Add a library to the project
add_library(${PROJECT_NAME} SHARED src/libPLcomparer.cpp)

# Add sources to a target
target_sources(${PROJECT_NAME} 
    PRIVATE src/libPLcomparer.cpp)

# Add include directories to a target
target_include_directories(${PROJECT_NAME} PRIVATE .)

# Minimum code requirements
set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  VERSION ${PROJECT_VERSION}
  SOVERSION  1
  PUBLIC_HEADER include/PLcomparer/PLcomparer.h
)

include_directories(include/)

# CLI libPLcomparer
add_executable(app src/PLcomparer.cpp)

find_package(CURL REQUIRED)

target_link_libraries(app ${PROJECT_NAME} CURL::libcurl)

# Examples
#add_subdirectory(examples)

### Install ###

# Standard GNU Directories
#include(GNUInstallDirs)

#install(TARGETS ${PROJECT_NAME}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})