# Set min req version of Cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(AD5697R_Driver_Lib)

# Set our lib include directories
include_directories(src inc)

# Set the lib output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)

# Create or our static library
ADD_LIBRARY( ad5697r STATIC src/ad5697r.c inc/ad5697r.h )

# Add a custom target for our unit tests
add_custom_target(tests cd ../ && ceedling gcov:all utils:gcov)