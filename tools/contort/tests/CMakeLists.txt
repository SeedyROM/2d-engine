cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME Contort_Test)
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 11)

# Sources
set(
        SOURCES
        test.c
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})