# Проверка версии CMake
cmake_minimum_required(VERSION 3.14) 

# Название проекта и проверка доступности компиляторя с++
project(pl-comparer VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

set(BUILD_SHARED_LIBS ON)

add_library(pl-comparer SHARED
  src/pl-comparer.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Минимальные требования кода
set_target_properties(
  pl-comparer PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  SOVERSION  1
  PUBLIC_HEADER include/pl-comparer/pl-comparer.h
)

# Добавьте исполняемый файл с указанными выше источниками
add_executable(example examples/main.cpp)

find_package(CURL REQUIRED)

target_link_libraries(example pl-comparer CURL::libcurl)

