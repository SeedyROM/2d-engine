cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME Contort)
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 11)

# Includes
include_directories(include)

# Sources
set(
        SOURCES

        src/main.c
        src/Tokenizer.c
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Tests
add_subdirectory(tests)