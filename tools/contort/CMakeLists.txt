cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME Contort)
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 11)

# Sources
set(
        SOURCES

        src/main.c
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})
