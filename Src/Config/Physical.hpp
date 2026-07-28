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

//╚═════════════════════════════════════ End of Dimensions ═════════════════════════════════════╝

// !SECTION Dimensions

// SECTION BLE information definitions

//╔═══════════════════════════ Start of BLE information definitions ════════════════════════════╗

	// Current hardware/software revisions and info
	#define ManufacturerName "Moonlit"
	#define ModelNumber "StarryBLE"
	#define HardwareRevision "1.0.0a"
	#define FirmwareRevision "0.0.5a"
	#define SoftwareRevision "N/A"

//╚════════════════════════════ End of BLE information definitions ═════════════════════════════╝

// !SECTION BLE information definitions

// SECTION Battery configurations

//╔═══════════════════════════════ Start of Battery configuration ══════════════════════════════╗

	// Max battery samples, leads to a more stable battery percent but can lead to a slower 
	// reaction to change
	#define BattSamples 10

	// Maximum battery voltage, 4.2 for a regular LiPo cell
	#define BattMaxVoltage 4.2

//╚════════════════════════════════ End of Battery configuration ═══════════════════════════════╝

// !SECTION Battery configurations