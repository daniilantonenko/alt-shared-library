# Checking the CMake
cmake_minimum_required(VERSION 3.14) 

# Project name and availability check C++ compiler
project(PLcomparer VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

include(GNUInstallDirs)
option(LIB_BUILD_EXAMPLES "Build examples" OFF)
option(LIB_BUILD_TESTS "Build tests" OFF)
option(LIB_BUILD_INSTALL "Install lib" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set the source files for the library
set(SOURCES src/libPLcomparer.cpp)

# Create the shared library target
add_library(${PROJECT_NAME}-shared SHARED ${SOURCES})

# Add sources to a target
target_sources(${PROJECT_NAME}-shared 
    PRIVATE src/libPLcomparer.cpp)

# Set the include directories for the library
target_include_directories(${PROJECT_NAME}-shared PUBLIC include)

# Minimum code requirements
set_target_properties(
  ${PROJECT_NAME}-shared PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  VERSION ${PROJECT_VERSION}
  SOVERSION  1
)

include_directories(include/)

# CLI libPLcomparer
add_executable(${PROJECT_NAME} src/PLcomparer.cpp)

find_package(CURL REQUIRED)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-shared CURL::libcurl)


if(LIB_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(LIB_BUILD_TESTS)
  target_compile_options(${PROJECT_NAME}-shared PUBLIC -fexceptions)
  enable_testing()
  add_subdirectory(tests)
endif()

if(LIB_BUILD_INSTALL)
  set(CMAKE_SKIP_BUILD_RPATH  FALSE)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


  install(TARGETS ${PROJECT_NAME}-shared
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  
  install(DIRECTORY include/
      TYPE INCLUDE
      COMPONENT ${PROJECT_NAME}-shared)

  install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})   
endif()