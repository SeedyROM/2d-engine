cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME 2DEngine)
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 11)

# Use our custom FindSDL2.cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Ignore weird dev warnings for SDL2 find_package
if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

# Includes
include_directories(
        include
        external
)

# Sources
set(
        SOURCES

        # Externals
        external/parson/parson.c

        # Entrypoint
        src/main.c

        # Code
        src/Configuration.c
        src/Error.c
        src/RenderContext.c
        src/ResourceManager.c
)

# ===================================================
# TODO: Copying assets into build
# Maybe this should be symlink in development?
# How do you do this? I'll ask the internet later
# ===================================================

# Copy Assets? Doesn't override old files :/
# file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(COPY config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# The game executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wextra -pedantic>) # Add -Wall -Werror later

# Link libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::GFX SDL2::TTF)