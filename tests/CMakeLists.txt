project(Tests)

#set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable (Boost_Tests_run test.cpp)
target_link_libraries (Boost_Tests_run PRIVATE 
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    PLcomparer-shared 
    CURL::libcurl)

add_test(Tests Boost_Tests_run)