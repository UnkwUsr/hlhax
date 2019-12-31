cmake_minimum_required(VERSION 3.3)
project(HlHack)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

include_directories(sdk/halflife-master/common
                    sdk/halflife-master/public
                    sdk/halflife-master/pm_shared
                    sdk/halflife-master/engine
                    src
                    )
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_compile_definitions(CMD_PREFIX="hx_")
add_compile_definitions(CVAR_PREFIX="cv_")

add_library(hlhack SHARED ${SOURCE_FILES})
