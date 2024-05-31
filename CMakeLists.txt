cmake_minimum_required(VERSION 3.10)

# Project name
project(Chess)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(Chess ${SOURCES})

# Set include directories
target_include_directories(Chess PRIVATE ${PROJECT_SOURCE_DIR}/include)
