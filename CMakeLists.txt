cmake_minimum_required(VERSION 3.3)
project(HlHack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -g")
SET(CMAKE_CXX_COMPILER clang++)

include_directories(sdk/halflife-master/common
                    sdk/halflife-master/public
                    sdk/halflife-master/pm_shared
                    sdk/halflife-master/engine
                    src
                    )
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
# copy inject tool to build directory
configure_file(inject_tool.sh ./
                   @ONLY)

add_compile_definitions(CMD_PREFIX="hx_")
add_compile_definitions(CVAR_PREFIX="cv_")

add_library(hlhack SHARED ${SOURCE_FILES})
