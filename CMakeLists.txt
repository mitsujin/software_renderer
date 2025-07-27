cmake_minimum_required(VERSION 3.16)
project(softrenderer VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable
add_executable(softrenderer 
    src/main.cpp
    src/Renderer.cpp
    src/Display.cpp
)

# Link libraries
target_link_libraries(softrenderer ${SDL2_LIBRARIES})

# Set compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(softrenderer PRIVATE -Wall -Wextra -O2)
endif()

# Copy SDL2 runtime libraries on Windows
if(WIN32)
    add_custom_command(TARGET softrenderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:softrenderer>
    )
endif() 