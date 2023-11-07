# Checking the CMake
cmake_minimum_required(VERSION 3.14) 

# Project name and availability check C++ compiler
project(plcomparer VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

include(GNUInstallDirs)
option(LIB_BUILD_EXAMPLES "Build examples" OFF)
option(LIB_BUILD_TESTS "Build tests" OFF)
option(LIB_BUILD_INSTALL "Install lib" OFF)

# Add executable
add_executable(${PROJECT_NAME} src/PLcomparer.cpp)

# Add shared library
add_library(libplcomparer SHARED src/libPLcomparer.cpp)

# Minimum code requirements
set_target_properties(
  libplcomparer PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  VERSION ${PROJECT_VERSION}
  SOVERSION  1
  PUBLIC_HEADER include/PLcomparer/PLcomparer.h
)

include_directories(include/)

find_package(CURL REQUIRED)

# Link executable with shared library
target_link_libraries(${PROJECT_NAME} PRIVATE libplcomparer CURL::libcurl)
set_target_properties(libplcomparer PROPERTIES OUTPUT_NAME "plcomparer")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")

# Path to the directory with include files
target_include_directories(libplcomparer PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Examples
############################################################

if(LIB_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

############################################################
# Testing
############################################################

if(LIB_BUILD_TESTS)
  target_compile_options(${PROJECT_NAME} PUBLIC -fexceptions)
  enable_testing()
  add_subdirectory(tests)
endif()

############################################################
# Install
############################################################

if(LIB_BUILD_INSTALL)

  # Setting the rules for installing a shared library
  install(TARGETS libplcomparer
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION /usr/local/include/PLcomparer
  )

  # Setting up rules for installing the executable and associated shared library
  install(TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif()