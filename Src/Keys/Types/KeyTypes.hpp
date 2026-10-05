#pragma once

#include <string>

// SECTION - Base key abstract

//╔═══════════════════════════════════════════════ Start of Base key abstract ═════════════════════════════════════════════╗

	/// @brief A simple base key
	class BaseKey {
		public:
			unsigned char Weight;

			inline BaseKey(unsigned char Weight) {
				this->Weight = Weight;
			};

			inline virtual std::string JSONParsed() = 0;
	};

//╚═══════════════════════════════════════════════ End of Base key abstract ═══════════════════════════════════════════════╝

// !SECTION - Base key abstract

// SECTION - SingleKey class

//╔══════════════════════════════════════════════════ Start of Single key ════════════════════════════════════════════════╗

	/// @brief A simple single char key
	class SingleKey : BaseKey {
		public:
			unsigned char USBKey;

			inline SingleKey(unsigned char Keycode) : BaseKey(1) {
				USBKey = Keycode;
			};

			inline std::string JSONParsed() override {
				return std::string("{\"Type\":1,\"Data\":{") + char(USBKey) + "}}";
			};
	};

//╚══════════════════════════════════════════════════ End of Single key ══════════════════════════════════════════════════╝

// !SECTION - SingleKey class

// SECTION - MultiKey class

//╔══════════════════════════════════════════════════ Start of Multi key ═════════════════════════════════════════════════╗

	/// @brief A simple single char key
	class MultiKey : BaseKey {
		public:
			unsigned char USBKeys[6] = {};

			unsigned char Size;

			inline MultiKey(unsigned char Keycodes[6], unsigned char Size) : BaseKey(Size) {
				for(unsigned char X = 0; X < Size; X++){
					USBKeys[X] = Keycodes[X];
				};
				this->Size = Size;
			};

			inline std::string JSONParsed() override {
				std::string Returnable = "{\"Type\":2,\"Data\":[";

				for (unsigned char X = 1; X <= Size; X++){
					Returnable += char(USBKeys[X]);
					if (X != Size){
						Returnable += ",";
					}
				}

				Returnable += "]}";
				return Returnable;
			};
	};

//╚══════════════════════════════════════════════════ End of Multi key ═══════════════════════════════════════════════════╝

// !SECTION - MultiKey class

// SECTION - TextKey class

//╔══════════════════════════════════════════════════ Start of Text key ══════════════════════════════════════════════════╗

	/// @brief A simple single char key
	class TextKey : BaseKey {
		public:
			std::string Text;

			inline TextKey(std::string Text) : BaseKey(6) {
				this->Text = Text;
			};

			inline std::string JSONParsed() override {
				return std::string("{\"Type\":3,\"Data\":\"") + Text + "\"}";
			};
	};

//╚══════════════════════════════════════════════════ End of Text key ════════════════════════════════════════════════════╝

// !SECTION - MultiKey class