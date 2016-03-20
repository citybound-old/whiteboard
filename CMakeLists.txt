cmake_minimum_required(VERSION 3.3)
project(whiteboard)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# dependencies

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
add_subdirectory(deps/glfw)

set(SOURCE_FILES
        main.cpp
        deps/nanovg/src/nanovg.c
)

add_executable(whiteboard ${SOURCE_FILES})

target_include_directories(whiteboard PUBLIC
        deps/glfw/include
        deps/nanovg/src
)

if(APPLE)
     set(CMAKE_CXX_LINK_FLAGS "-framework Cocoa -framework QuartzCore -framework OpenGL")
endif(APPLE)

target_link_libraries(whiteboard glfw ${GLFW_LIBRARIES})