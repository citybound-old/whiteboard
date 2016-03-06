cmake_minimum_required(VERSION 3.3)
project(WhiteboardDemo)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# dependencies

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
add_subdirectory(deps/glfw)

include_directories(
        deps/glfw/include
        deps/nanovg/src
)

set(SOURCE_FILES
        main.cpp
)
add_executable(WhiteboardDemo ${SOURCE_FILES})

add_library(nanovg deps/nanovg/src/nanovg.c)

if(APPLE)
     set(CMAKE_CXX_LINK_FLAGS "-framework Cocoa -framework QuartzCore -framework OpenGL")
endif(APPLE)

set(WHITEBOARD_LIBRARIES
        nanovg
        glfw
        ${GLFW_LIBRARIES}
)

target_link_libraries(WhiteboardDemo ${WHITEBOARD_LIBRARIES})