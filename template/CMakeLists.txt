# Set min req version of Cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(AD56x_Example_Main)

# Set our lib include directories
include_directories(../inc)

# Create the C Executable
add_executable(ad56x main.c)
# Link against our icm20948 lib
TARGET_LINK_LIBRARIES(ad56x "${CMAKE_SOURCE_DIR}/../lib/libad56x.a")