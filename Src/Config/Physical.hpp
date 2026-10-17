#pragma once

/*

Physical data configuration
A file which allows the simple modification of general physical properties

*/

// SECTION Dimensions

//╔════════════════════════════════════ Start of Dimensions ════════════════════════════════════╗
//	*- Note: due to the use of a compact vector 2, a size of 15x15 is the maximum allowed

	// X dimension of the keyboard in buttons 
	#define SizeX 5

	// Y dimension of the keyboard in buttons
	#define SizeY 5

	// Bus GPIOs, AKA Outpins, must be equal to SizeX
	#define XGPIOs 5,6,7,8,9 

	// In GPIOs, AKA Inpins, must be equal to SizeY
	#define YGPIOs 0,1,2,3,4

//╚═════════════════════════════════════ End of Dimensions ═════════════════════════════════════╝

// !SECTION Dimensions

// SECTION BLE information definitions

//╔═══════════════════════════ Start of BLE information definitions ════════════════════════════╗

	// Current hardware/software revisions and info
	#define ManufacturerName "Moonlit"
	#define ModelNumber "StarryBLE"
	#define HardwareRevision "3.0.0"
	#define FirmwareRevision "0.1.0a"
	#define SoftwareRevision "N/A"

//╚════════════════════════════ End of BLE information definitions ═════════════════════════════╝

// !SECTION BLE information definitions

// SECTION Battery configurations

//╔═══════════════════════════════ Start of Battery configuration ══════════════════════════════╗

	// Max battery samples, leads to a more stable battery percent but can lead to a slower 
	// reaction to change
	#define BattSamples 10

	// Amount of delay time between each battery update, note that battery readings will still
	// remain one per cycle, usually being every 10 ms per cycle
	#define BattReadingDelayCycles 200

	// Maximum battery voltage, 4.2 for a regular LiPo cell
	#define BattMaxVoltage 4.2

	// Minimum battery voltage, 3.2 for a regular setup
	#define BattMinVoltage 3.2

//╚════════════════════════════════ End of Battery configuration ═══════════════════════════════╝

// !SECTION Battery configurations

// SECTION LED configurations

//╔═════════════════════════════════ Start of LED configuration ════════════════════════════════╗

	// Comment/Uncomment definitions to toggle useage of LED GPIOs
	// These must also be equal to the GPIO they control

	// Num lock GPIO 
	#define NumLockGPIO 13

	// Caps lock GPIO
	#define CapsLockGPIO 12

	// Scroll lock GPIO
	#define ScrollLockGPIO 14

	// Compose GPIO
	//#define ComposeGPIO

	// Kana GPIO
	//#define KanaGPIO

	// Key underlight toggle
	#define PMOSCtrl 5

	// NOTE: Timer shouldn't be commented out, it's only used if PMOSCtrl is enabled

	// Key underlight delay
	#define PMOSTurnOff 1000

//╚══════════════════════════════════ End of LED configuration ═════════════════════════════════╝

// !SECTION Battery configurations

// SECTION Hardware characteristics

//╔══════════════════════════════ Start of Hardware characteristics ════════════════════════════╗

	// Comment/Uncomment to define board hardware characteristics

	// Presence of a schmitt trigger NOT gate chip (such as 74HC14)
	//#define SchmittInvert

//╚═══════════════════════════════ End of Hardware characteristics ═════════════════════════════╝

// !SECTION Hardware characteristics

// SECTION Memory

//╔═══════════════════════════════════════ Start of Memory ═════════════════════════════════════╗

	// If defined, make use of I2C0, otherwise use I2C1
	// #define UseI2C0

	// GPIO used for SDA memory interface
	#define MemSDAGPIO 10

	// GPIO used for SCL memory interface
	#define MemSCLGPIO 11

//╚════════════════════════════════════════ End of Memory ══════════════════════════════════════╝

// !SECTION Hardware characteristics