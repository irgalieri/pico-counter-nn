# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/pi/working-copy/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt)

project(pico-counter-nn C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pico-counter-nn pico-counter-nn.c )

pico_set_program_name(pico-counter-nn "pico-counter-nn")
pico_set_program_description(pico-counter-nn "Counter Pico With Seven Segment Leds.")
pico_set_program_url(pico-counter-nn "https://github.com/irgalieri/pico-counter-nn")
pico_set_program_version(pico-counter-nn "0.1")

pico_enable_stdio_uart(pico-counter-nn 1)
pico_enable_stdio_usb(pico-counter-nn 0)

# Add the standard library to the build
target_link_libraries(pico-counter-nn pico_stdlib)

# Add any user requested libraries
target_link_libraries(pico-counter-nn
    pico_multicore
    pico_binary_info
    h595-shift-register-nn
)

pico_add_extra_outputs(pico-counter-nn)

