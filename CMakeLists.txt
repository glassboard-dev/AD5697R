# Set min req version of Cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(AD56x_Driver_Lib)

# Set our lib include directories
include_directories(src inc)

# Set the lib output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)

# Create or our static library
ADD_LIBRARY( ad56x STATIC src/ad56x.c inc/ad56x.h )

# Add a custom target for our unit tests
add_custom_target(tests cd ../ && ceedling gcov:all utils:gcov)