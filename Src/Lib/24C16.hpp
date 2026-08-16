#include <Src/Util/Data.hpp>
#include "hardware/i2c.h"

// SECTION Chip class

//╔═════════════════════════════════════════════════ Start of Chip class ═══════════════════════════════════════════════╗

	/// @brief C++ implementation of a 24C16 16Kb memory
	class Mem24C16 {
		private:

			/// @brief 0b10100000 base address for all 24C16 chips
			static const unsigned char BaseAddress = 0x50;
			
			/// @brief SDA pin for I2C communications
			unsigned char SDAPin;

			/// @brief SCL pin for I2C communications
			unsigned char SCLPin;

			i2c_inst_t* UseableI2CBus = i2c0;

			/// @brief Storage spot for a single byte
			unsigned char SingleByteBuffer[1] = {0};

			/// @brief Initializes all required pins for chip to function
			void InitPins();

			/// @brief Delays next action by set pin delay
			static inline void Delay(){
				sleep_ms(PinDelay);
			};

			/// @brief Parses a target number into an address and offset
			/// @param Target Target number to store the value at
			/// @param Address Block to visit
			/// @param Offset Offset in block to visit
			static void ParseAddress(unsigned int Target, unsigned char* Address, unsigned char* Offset);

		public:

			/// @brief Amount of delay to wait for chip to settle in mS
			static inline unsigned int PinDelay = 5;

			static const unsigned int Length = 2048;

			static const unsigned int BlockSize = 256;

			/// @brief Creates an 24C16 object with given GPIOs initialized
			/// @param Data SDA enabled pin for I2C communications
			/// @param Clock SCL enabled pin for I2C communications
			/// @param I2CBus I2C0 or I2C1 bus to be used
			Mem24C16(unsigned const char Data, unsigned const char Clock, i2c_inst_t* I2CBus);

			/// @brief Returns the value stored in given target
			/// @param Target Position in EEPROM to read from
			/// @return Value currently stored within the EEPROM
			unsigned char GetValue(unsigned int Target);

			/// @brief Stores a given value within the EEPROM
			/// @param Target Position to store value at
			/// @param Value Value to store
			void SetValue(unsigned int Target, unsigned char Value);
	};

//╚═════════════════════════════════════════════════ End of Chip class ═════════════════════════════════════════════════╝

// !SECTION Chip class