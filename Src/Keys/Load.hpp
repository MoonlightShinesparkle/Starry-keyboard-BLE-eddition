#pragma once

#include <Src/Lib/24C16.hpp>

// SECTION - MemMisc

//╔═════════════════════════════════════════════════ Start of Mem misc ═══════════════════════════════════════════════╗

	/// @brief Format specific magic number
	const unsigned char MagicNo[] = {
		0x53, 0x74, 0x61, 0x72, // Star
		0x72, 0x79, 0x4B, 0x62, // ryKb
		0x64, 0x46, 0x6F, 0x72, // dFor
		0x6D       				// m
	};

	/// Index that defines a data block belonging to a simple key press
	#define KeyInd 0x01

	/// Index that defines a data block belonging to a multikey array
	#define MultiInd 0x02

	/// Index that defines a data block belonging to a text key
	#define TextInd 0x03

	/// Index that defines the file's end
	#define FileEnd 0x04

	/// Default data array size (X)
	#define DefaultKeysSizeX = 5

	/// Default data array size (Y)
	#define DefaultKeysSizeY = 5

	/**
	 * @brief A bidimensional array of default data for a keyboard
	 * in case a key is broken or there's less data present than required
	 * @note The default layout is as follows:
	 * @note M O N L I
	 * @note G H T W A
	 * @note S E R ; 3
	 * @note * O . = -
	 * @note Where * is bootsel
	 */
	const unsigned char DefaultKeys[5][5]{
		// Moonlight was here layout
		{0x10,0x12,0x11,0x0F,0x0C},
		{0x0A,0x0B,0x17,0x1A,0x04},
		{0x16,0x08,0x15,0x33,0x20},
		{0x2C,0x28,0xE1,0x39,0x2A},
		{0xE8,0x27,0x37,0x2E,0x2D}
	};

//╚═════════════════════════════════════════════════ End of Mem misc ═════════════════════════════════════════════════╝

// !SECTION - MemMisc

// SECTION - Starry parser class

//╔══════════════════════════════════════════════ Start of Starry parser ═════════════════════════════════════════════╗



//╚══════════════════════════════════════════════ End of Starry parser ═══════════════════════════════════════════════╝

// !SECTION - Starry parser class