# Checking the CMake
cmake_minimum_required(VERSION 3.14) 

# Project name and availability check C++ compiler
project(PLcomparer VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

# Add a library to the project
add_library(${PROJECT_NAME}-shared SHARED src/libPLcomparer.cpp)

# Add sources to a target
target_sources(${PROJECT_NAME}-shared 
    PRIVATE src/libPLcomparer.cpp)

# Add include directories to a target
target_include_directories(${PROJECT_NAME}-shared PRIVATE .)

# Minimum code requirements
set_target_properties(
  ${PROJECT_NAME}-shared PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  VERSION ${PROJECT_VERSION}
  SOVERSION  1
  PUBLIC_HEADER include/PLcomparer/PLcomparer.h
)

include_directories(include/)

# CLI libPLcomparer
add_executable(${PROJECT_NAME} src/PLcomparer.cpp)

find_package(CURL REQUIRED)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-shared CURL::libcurl)

# Examples
#add_subdirectory(examples)

### Install ###

if (UNIX)
  include(GNUInstallDirs)

  install(TARGETS ${PROJECT_NAME}-shared
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

  install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})   

  set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif ()