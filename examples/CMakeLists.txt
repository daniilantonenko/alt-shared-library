project(Examples)

# Executable
add_executable(example1 compare_and_save.cpp)
add_executable(example2 compare_and_print.cpp)

# Add required libraries
target_link_libraries(example1 PLcomparer CURL::libcurl)
target_link_libraries(example2 PLcomparer CURL::libcurl)
