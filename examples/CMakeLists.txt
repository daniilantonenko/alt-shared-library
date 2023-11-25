project(Examples)

# Executable
add_executable(compare_and_save compare_and_save.cpp)
add_executable(compare_and_print compare_and_print.cpp)

# Add required libraries
target_link_libraries(compare_and_save libplcomparer CURL::libcurl)
target_link_libraries(compare_and_print libplcomparer CURL::libcurl)