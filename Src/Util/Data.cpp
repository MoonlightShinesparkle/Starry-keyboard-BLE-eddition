#include "Data.hpp"
#include <cstdarg>

// SECTION - CompactVec2

//╔═════════════════════ Start of CompactVec2 functions ════════════════════╗
//║ *- Get X and Y components of the value:									║
//║ Value = 0b  0000  0000													║
//║				└──┘  └──┘													║
//║				 X		Y													║

	unsigned char CompactVec2::GetX(){
		return (Value >> 4) & 0xF;
	}

	unsigned char CompactVec2::GetY(){
		return Value & 0xF;
	}

	void CompactVec2::SetX(unsigned char X){
		unsigned char Masked = Value & 0xF;
		Value = Masked | (X << 4);
	}

	void CompactVec2::SetY(unsigned char Y){
		unsigned char Masked = Value & 0xF0;
		Value = Masked | (Y & 0xF);
	}

	void CompactVec2::SetValues(unsigned char X, unsigned char Y){
		Value = (X << 4) | (Y & 0xF);
	}
	
	CompactVec2::CompactVec2(unsigned char X, unsigned char Y) : Value(0){
		SetValues(X,Y);
	}

//╚══════════════════════ End of CompactVec2 functions ═════════════════════╝

// !SECTION - CompactVec2
// SECTION - GPIO

//╔════════════════════════ Start of GPIO functions ════════════════════════╗

	void SetAsOutput(uint GPIO){
		gpio_init(GPIO);
		gpio_set_dir(GPIO, GPIO_OUT);
	}

	void SetAsInput(uint GPIO, bool PullDown = false){
		gpio_init(GPIO);
		gpio_set_dir(GPIO,GPIO_IN);
		if (PullDown){
			gpio_pull_down(GPIO);
		}
	}

//╚═════════════════════════ End of GPIO functions ═════════════════════════╝

// !SECTION - GPIO