#pragma once

#include <iostream>
#include <math.h>
#include "Descriptors/HIDData.hpp"
#include "Config/Physical.hpp"
#include "Keys/Keys.hpp"

extern "C"{
	#include "Descriptors/btstack_config.h"
	#include "btstack.h"
	#include "btstack_tlv.h"

	#include "ble/gatt-service/battery_service_server.h"
	#include "ble/gatt-service/device_information_service_server.h"
	#include "ble/gatt-service/hids_device.h"

	#include "pico/cyw43_arch.h"
	#include "pico/btstack_cyw43.h"
	#include "pico/stdlib.h"
	#include "pico/unique_id.h"

	#include "hardware/adc.h"

	#include "StarryBLE.h"
}

// std cout shortcut
#define COut(Txt) std::cout << Txt << std::endl

// SECTION Bluetooth chaos

//╔═══════════════════════════════════════════════ Start of Bluetooth chaos ═══════════════════════════════════════════════╗

	// Delay between bluetooth reports
	#define Delay 10

	// TLV HIDR value
	#define TLVHidr ((((uint32_t) 'H') << 24 ) | (((uint32_t) 'I') << 16) | (((uint32_t) 'D') << 8) | 'R')

	// HCI event registry
	static inline btstack_packet_callback_registration_t HCIEventRegist;
	
	// L2CAP event registry
	static inline btstack_packet_callback_registration_t L2CAPEventRegist;
	
	// SM event registry
	static inline btstack_packet_callback_registration_t SMEventRegist;
	
	// Main timer
	static inline btstack_timer_source_t MainTimer;
	
	// Bluetooth address
	static inline bd_addr_t BTAddr;
	
	// HCI connection handle
	static inline hci_con_handle_t HCICon = HCI_CON_HANDLE_INVALID;

	// Protocol used for key report sending
	static inline unsigned char Protocol = 1;
	
	// BoardID size
	const inline unsigned char BoardIDSize = 2 * PICO_UNIQUE_BOARD_ID_SIZE_BYTES + 1;
	
	// Board ID buffer
	static inline char BoardID[BoardIDSize] = "";

	/// @brief Handles pawkets in BLE
	/// @param PawketType 
	/// @param Channel 
	/// @param Pawket 
	/// @param Size 
	static void PawketHandler(unsigned char PawketType, unsigned short Channel, unsigned char* Pawket, unsigned short Size);
	
	/// @brief Sends a data report through the specified protocol
	static void SendData();
	
	/// @brief Sets up BLE services and pawket handler
	static void MainSetup();

	/// @brief Main function for bluetooth stack functions
	/// @param argc Argument count
	/// @param argv Arguments
	/// @return Error code
	int btstack_main(int argc, const char * argv[]);

//╚════════════════════════════════════════════════ End of Bluetooth chaos ════════════════════════════════════════════════╝

// !SECTION Bluetooth chaos

// SECTION Battery management

//╔══════════════════════════════════════════════ Start of Battery management ═════════════════════════════════════════════╗

	// True battery maximum considering min voltage
	#define BattTrueMaximum BattMaxVoltage - BattMinVoltage

	// Represents the current battery level of the device
	static inline unsigned char BatteryLvl = 100;

	// Acquired battery reads
	static inline double BattReadings[BattSamples] = {};

	// Current slot for battery reads
	static inline unsigned char BattReadingIndex = 0;

	// Current cycle of delay for a batt update
	static inline unsigned char BattCycle = 0;

	/// @brief Initializes the battery ADC vars required for voltage acquisition
	/// @note Fills in battery voltage array
	static void BattADCInnit();

	/// @brief Fills next spot in BattReadings, updating old values
	static void DoNextReading();
	
	/// @brief Obtains the battery voltage from ADC0
	/// @note Voltage is halved due to resistor divider, a pico can't handle a batt's raw voltage
	/// @return Current batt voltage
	static double AcquireBattVoltage();
	
	/// @brief Calculates the battery percent based on the currently loaded batt array
	/// @note Loads into BatteryLvl var
	static void AcquireBattPercent();

//╚═══════════════════════════════════════════════ End of Battery management ══════════════════════════════════════════════╝

// !SECTION Battery management

// SECTION Key management

//╔════════════════════════════════════════════════ Start of Key management ═══════════════════════════════════════════════╗

	// Current keyboard modifiers
	static inline unsigned char Modifiers = 0;

	// Collection of cached keycodes
	static inline unsigned char CachedKeycodes[6] = {0,0,0,0,0,0};

	// Defines wheter or not the modifier bit should be calculated based on current keycodes
	static inline bool CalculateModifier = true;

	/// @brief Readies up keycodes into cache and triggers sending them
	/// @param TimerSource Bluetooth timer to reincorporate into run loop
	static void LoadScan(btstack_timer_source_t* TimerSource);

	/// @brief Sends a single key to the cache (clearing it) and triggers sending them
	/// @param Modif Modifier bit
	/// @param Chr Keycode to send
	static void SendKey(unsigned char Modif, unsigned char Chr);

	/// @brief Initiates the key acquisition loop by setting up timers
	static void KeyAcquisLoop();

	/// @brief Returns the modifier bit of a given key
	/// @param Keycode Current keycode
	/// @return Shifted bit that represents the key's modifier bit
	static unsigned char ModifierBit(unsigned char Keycode);

//╚═════════════════════════════════════════════════ End of Key management ════════════════════════════════════════════════╝

// !SECTION Key management