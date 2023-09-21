cmake_minimum_required(VERSION 3.13)

#set(CMAKE_GENERATOR "Ninja")
message("generator is set to ${CMAKE_GENERATOR}")

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(led_module)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add WS2812B_Module
file(GLOB WS2812B
    "src/*.cpp"
    "src/*.h"
)

# Add main file with other libs
add_executable(
    ${CMAKE_PROJECT_NAME} # Executable
    main.cpp
    ${WS2812B}
)

# Enable USB
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1) # USB

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

# ========== ADD LCOMPILED LIBRARIES ========== #
# ============================================= #
# * pico_stdlib

target_link_libraries(${CMAKE_PROJECT_NAME} pico_stdlib)

