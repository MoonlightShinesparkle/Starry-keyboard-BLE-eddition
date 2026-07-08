#pragma once

#include <iostream>
#include "Descriptors/HIDData.hpp"

#include "btstack.h"

#include "ble/gatt-service/battery_service_server.h"
#include "ble/gatt-service/device_information_service_server.h"
#include "ble/gatt-service/hids_device.h"

#include "pico/cyw43_arch.h"
#include "pico/btstack_cyw43.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/unique_id.h"

extern "C" {
	#include "StarryBLE.h"
}

#define COut(Txt) std::cout << Txt << std::endl

// Handles pawkets in BLE
static void PawketHandler(unsigned char PawketType, unsigned short Channel, unsigned char* Pawket, unsigned short Size);