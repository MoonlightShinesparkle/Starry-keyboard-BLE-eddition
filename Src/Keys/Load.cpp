#include "Load.hpp"

// SECTION - Starry parser class

//╔══════════════════════════════════════════════ Start of Starry parser ═════════════════════════════════════════════╗	

	void LoadKeys(Mem24C16 Source, BaseKey* Destination[SizeY][SizeX]){
		// Verify memory containing relevant data
		if (!VerifyMem(Source)){
			std::cout << "[LoadKeys] Problem while verifying memory, loading defaults" << std::endl;
			LoadDefaults(Destination);
			return;
		}

		// Memory passed and is ready for general procedure
		std::cout << "[LoadKeys] Header found, reading from memory" << std::endl;
		
		// Required key pawsition values
		unsigned char X = 0;
		unsigned char Y = 0;
		// Main key acquisition loop
		for (unsigned int C = 13; C < Source.Length; C++){
			if (X >= SizeX){
				Y++;
				X = 0;
			}
			if (Y >= SizeY){
				std::cout << "[LoadKeys] Found all required keys" << std::endl;
				break;
			}

			switch (Source.GetValue(C)) {
				case KeyInd: {
					// NOTE: Found key index
					C++;
					// Format is pretty simple: just get the next value, that's the key
					unsigned char Acquired = Source.GetValue(C);

					SingleKey Insertable = SingleKey(Acquired);

					// Load key data into slot
					Destination[Y][X] = &Insertable;
					std::cout << "[LoadKeys] Loaded SingleKey [" << (int)Acquired << "]" << std::endl; 

					// Increment slot by 1 as it has been loaded
					X++;
					break;
				} case MultiInd: {
					// NOTE: Found multikey index
					C++;
					// Format is more developed: the next value is the quantity, there's quantity keys around

					// Get length of key array
					unsigned char KeyLength = Source.GetValue(C);

					// Max size key cache
					unsigned char KeyCache[6];

					std::cout << "[LoadKeys] Loading MultiKey [" << (int)KeyLength << "] {";

					// Loop through key length
					for(unsigned char V = 0; V < KeyLength; V++){
						// Increment C regardless of if the value is useful or not, we want C at the end of the chain
						C++;
						// If there's space, load character
						if (V < 6){
							KeyCache[V] = Source.GetValue(C);
							std::cout << (int)KeyCache[V] << ',';
						}
					}

					std::cout << '}' << std::endl;

					MultiKey Insertable = MultiKey(KeyCache,KeyLength);

					// Load data into destination
					Destination[Y][X] = &Insertable;

					// Move towards next slot
					X++;
					break;
				} case TextInd: {
					// NOTE: Found text index
					C++;
					// Similar to multikey, but there's no keys, only chars, i mean true chars, not bytes

					// Get size
					unsigned char KeyLength = Source.GetValue(C);

					// String
					std::string Stringified = "";

					// Iteratethrough KeyLength steps
					for(unsigned char _ = 0; _ < KeyLength; _++){
						C++;
						Stringified += Source.GetValue(C);
					}

					// Turn string into TextKey
					TextKey Insertable = TextKey(Stringified);

					Destination[Y][X] = &Insertable;

					std::cout << "[LoadKeys] Loaded Textkey [" << Stringified << ']' << std::endl;

					// Move towards next slot
					X++;
					break;
				} default: {
					break;
				}
			}
		}

		// Looked through everything pawsible, found mising data, filling with OOR (out of range) key
		while (Y < SizeY) {
			// Keep same wrapping logic as beforepaw
			if (X >= SizeX){
				Y++;
				X = 0;
			}

			SingleKey Insertable = SingleKey(DefaultIfOORKey);
			// Load basic key
			Destination[Y][X] = &Insertable;
			// Go to next slot since C is meaningless at this point
			X++;
		}
		
	}

	static bool VerifyMem(Mem24C16 Source){
		std::cout << "[LoadKeys] First values from EEPROM: ";
		for (unsigned char X = 0; X < 20; X++){
			unsigned char Given = Source.GetValue(X);
			if (Given > 32){
				std::cout << Given;
			} else {
				std::cout << '[' << (int)Given << ']';
			}
		}
		std::cout << std::endl;

		// Loop through memory and array
		for (unsigned char X = 0; X < 13; X++){
			// Acquire values to compare
			unsigned char Fetched = Source.GetValue(X);
			unsigned char Expected = MagicNo[X];

			std::cout << "[LoadKeys] Comparing " << Fetched << " and " << Expected << std::endl;

			// Check if values differ
			if (Fetched != Expected){
				// Failure
				return false;
			}
		}
		// Checked through all chars, 0 Failures
		return true;
	}

	static void LoadDefaults(BaseKey* Destination[SizeY][SizeX]){
		// Loop through every destination box
		for (unsigned char Y = 0; Y < SizeY; Y++){
			for (unsigned char X = 0; X < SizeX; X++){
				// Insertable is a default key within the default array or the default OOR key (to account for bigger starry keyboards)
				unsigned char Insertable = ((Y < DefaultKeysSizeY) & (X < DefaultKeysSizeX)) ? DefaultKeys[Y][X] : DefaultIfOORKey;
				// Turn into a generic single key and toss into array
				SingleKey Referenceable = SingleKey(Insertable);
				Destination[Y][X] = &Referenceable;
			}
		}
	}

//╚══════════════════════════════════════════════ End of Starry parser ═══════════════════════════════════════════════╝

// !SECTION - Starry parser class