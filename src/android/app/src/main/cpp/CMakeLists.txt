cmake_minimum_required(VERSION 3.22.1)

project("luna")

include_directories("../../../../../../src")

add_library(luna SHARED native-lib.cpp)

find_library(log-lib log)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(luna ${log-lib} ${jnigraphics-lib})
