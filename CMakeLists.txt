cmake_minimum_required(VERSION 3.23)

# Since visual studio code won't detect zsh exported variables...
set(PICO_SDK_PATH "/Users/mac/Documents/PicoWorkspace/Pico")
include(pico_sdk_import.cmake)
project(LuaCalc C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

pico_sdk_init()
add_subdirectory(src/Modules/SD/FatFs_SPI/src build) 

add_executable(${PROJECT_NAME}
	src/Modules/GUI/LCD/lcd1602_i2c.c
	src/Data.cpp
	src/Keys.cpp
	src/Kernel.cpp
	src/hw_config.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_multicore
	hardware_i2c
	no-OS-FatFS-SD-SDIO-SPI-RPi-Pico
)