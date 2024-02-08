cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(EmbeddedSnake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(waveshare-lib/GUI)
add_subdirectory(waveshare-lib/Config)
add_subdirectory(waveshare-lib/LCD)
add_subdirectory(waveshare-lib/Infrared)
add_subdirectory(waveshare-lib/Icm20948)
add_subdirectory(waveshare-lib/OLED)
add_subdirectory(waveshare-lib/Fonts)

include_directories(waveshare-lib/Config)
include_directories(waveshare-lib/GUI)
include_directories(waveshare-lib/Infrared)
include_directories(waveshare-lib/LCD)
include_directories(waveshare-lib/Icm20948)
include_directories(waveshare-lib/OLED)
include_directories(waveshare-lib/Fonts)

add_compile_options(--sysroot=/usr/arm-none-eabi)
add_executable(program 
    main.c
    game.c
    input.c
    snake.c
    world.c
    drawing.c
)


target_link_libraries(program PUBLIC pico_stdlib GUI Config LCD Infrared OLED Icm20948 Fonts)
pico_add_extra_outputs(program)

pico_enable_stdio_usb(program 1)
pico_enable_stdio_uart(program 0)