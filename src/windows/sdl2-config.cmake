set(SDL2_PATH "C:/Programming/c++/luna/3dparty/SDL2-2.26.3")

set(SDL2_INCLUDE_DIRS "${SDL2_PATH}/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${SDL2_PATH}/lib/x64/SDL2.lib;${SDL2_PATH}/lib/x64/SDL2main.lib")
else ()
  set(SDL2_LIBRARIES "${SDL2_PATH}/lib/x86/SDL2.lib;${SDL2_PATH}/lib/x86/SDL2main.lib")
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)