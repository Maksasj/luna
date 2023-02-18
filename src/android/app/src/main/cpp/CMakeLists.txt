cmake_minimum_required(VERSION 3.22.1)

project("luna")

include_directories("../../../../../../src/shared")

file(GLOB LUNA_SOURCE
     "*.h"
     "*.cpp"
     "../../../../../../src/shared/*.cpp"

     "../../../../../../src/shared/events/*.cpp"
     "../../../../../../src/shared/rendering/*.cpp"
     "../../../../../../src/shared/utils/*.cpp"
)

add_library(luna SHARED ${LUNA_SOURCE})

find_library(log-lib log)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(luna ${log-lib} ${jnigraphics-lib})
