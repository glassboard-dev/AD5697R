# Set min req version of Cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(ad5697r_Example_Main)

# Set our lib include directories
include_directories(../inc)

# Create the C Executable
add_executable(ad5697r main.c)
# Link against our icm20948 lib
TARGET_LINK_LIBRARIES(ad5697r "${CMAKE_SOURCE_DIR}/../lib/libad5697r.a")