cmake_minimum_required(VERSION 3.1.0)
project(InOneWeekend LANGUAGES CXX)

# Add the Eigen include directory
include_directories(${CMAKE_SOURCE_DIR}/eigen-3.4.0)

# Set to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the source files for the executable
set(SOURCE_FILES main.cpp) # Adjusted the path

# Compiler options
if(MSVC)
    add_compile_options("/W4")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Add the executable
add_executable(inOneWeekend ${SOURCE_FILES})

# Set the output name of the executable to 'inOneWeekend.exe' (optional, as it will default to the project name)
set_target_properties(inOneWeekend PROPERTIES OUTPUT_NAME "inOneWeekend")
