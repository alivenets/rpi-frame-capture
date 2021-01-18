cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(PiScreenCapture LANGUAGES C)

set(CMAKE_SYSROOT "/home/develop/RPi-sysroot")

set(CMAKE_CXX_COMPILER aarch64-rpi3-linux-gnu-g++)
set(CMAKE_C_COMPILER aarch64-rpi3-linux-gnu-gcc)

add_library(PiScreenCapture rpi_capture.c)
target_include_directories(PiScreenCapture PUBLIC "${CMAKE_SYSROOT}/opt/vc/include")
link_directories("${CMAKE_SYSROOT}/opt/vc/lib")
target_link_libraries(PiScreenCapture PUBLIC bcm_host vchostif)

add_executable(test-rpi-screenshot main.c)
target_link_libraries(test-rpi-screenshot PiScreenCapture)
