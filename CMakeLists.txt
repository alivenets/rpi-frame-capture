cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(PiScreenCapture LANGUAGES C)

set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

add_library(PiScreenCapture rpi_capture.c)
target_include_directories(PiScreenCapture PUBLIC "/opt/vc/include")
target_link_directories(PiScreenCapture PUBLIC "/opt/vc/lib")
target_link_libraries(PiScreenCapture PUBLIC bcm_host vchostif)

add_executable(test-rpi-screenshot main.c)
target_link_libraries(test-rpi-screenshot PiScreenCapture)
