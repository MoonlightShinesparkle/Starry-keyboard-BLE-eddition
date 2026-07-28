cmake_minimum_required(VERSION 3.23)

set(PICO_BOARD pico2_w)

# Since visual studio code won't detect zsh exported variables...
if (NOT DEFINED ENV{PICO_SDK_PATH})
	set(PICO_SDK_PATH "/Users/mac/Documents/PicoWorkspace/Pico")
endif()
include(pico_sdk_import.cmake)
project(PicoWBLEKbd C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

pico_sdk_init()

message("Pico variables found:")
message(STATUS "PICO_SDK_PATH=${PICO_SDK_PATH}")
message(STATUS "PICO_CYW43_SUPPORTED=${PICO_CYW43_SUPPORTED}")
message(STATUS "PICO_BTSTACK_PATH=${PICO_BTSTACK_PATH}")

if (NOT PICO_CYW43_SUPPORTED)
	message(WARNING "No CYW43 support")
    return()
endif()
if (DEFINED ENV{PICO_BTSTACK_PATH} AND (NOT PICO_BTSTACK_PATH))
    set(PICO_BTSTACK_PATH $ENV{PICO_BTSTACK_PATH})
    message("Using PICO_BTSTACK_PATH from environment ('${PICO_BTSTACK_PATH}')")
endif ()
set(BTSTACK_TEST_PATH "src/bluetooth.h")
if (NOT PICO_BTSTACK_PATH)
    set(PICO_BTSTACK_PATH ${PICO_SDK_PATH}/lib/btstack)
    if (PICO_CYW43_SUPPORTED AND NOT EXISTS ${PICO_BTSTACK_PATH}/${BTSTACK_TEST_PATH})
        message(WARNING "btstack submodule has not been initialized; Pico Bluetooth support will be unavailable.
            hint: try 'git submodule update --init' from your SDK directory (${PICO_SDK_PATH}).")
    endif()
elseif (NOT EXISTS ${PICO_BTSTACK_PATH}/${BTSTACK_TEST_PATH})
    message(WARNING "PICO_BTSTACK_PATH specified but content not present.")
endif()

add_executable(${PROJECT_NAME}
    Src/Keys/Keys.cpp
    Src/Util/Data.cpp
	Src/Main.cpp
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_multicore
	pico_btstack_ble
    pico_btstack_cyw43
    pico_cyw43_arch_none
	pico_unique_id
	hardware_i2c
    hardware_adc
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
	Src/Config
	Src/Descriptors
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    #WANT_HCI_DUMP=1
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_btstack_make_gatt_header(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Src/Descriptors/StarryBLE.gatt")
pico_add_extra_outputs(${PROJECT_NAME})