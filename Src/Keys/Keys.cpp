#include "Keys.hpp"
#include "pico/bootrom.h"

#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25
#endif

/* 

Keys module
Contains different functions for managing the keyboard itself in a physical level, storing data in the form of keys

*/

// SECTION Key IO & setup functions

//╔═══════════════════════════ Start of Key IO & setup functions ═══════════════════════════╗

	void SetKeyboardInput(uchar GPIO){
		SetAsInput(GPIO, false);
		gpio_pull_up(GPIO);
	}

	void SetupKeys(){
		for (uchar Inpin : KeyboardInputs){
			SetAsOutput(Inpin);
			gpio_put(Inpin,1);
		}
		for (uchar Outpin : KeyboardOutputs){
			SetKeyboardInput(Outpin);
		}
	}

//╚════════════════════════════ End of Key IO & setup functions ════════════════════════════╝

// !SECTION Key IO & setup functions

// SECTION Key array functions

//╔══════════════════════════════ Start of Key array functions ═════════════════════════════╗

	bool KeysPressed[SizeY][SizeX];
	Key KeysJustPressed[CachedKeys];
	Key KeysPressing[CachedKeys];
	uchar NumKeysPressed = 0;

	bool IsInKeyList(Key LookFor, Key In[CachedKeys], int &Position){
		bool Returnable = false;
		Position = -1;
		for (uchar i = 0; i < CachedKeys; i++){
			uchar Val = In[i];
			if (Val == LookFor){
				Returnable = true;
				Position = i;
				break;
			}
		}
		return Returnable;
	}

	bool IsInKeyList(Key LookFor, Key In[CachedKeys]){
		bool Returnable = false;
		for (uchar i = 0; i < CachedKeys; i++){
			uchar Val = In[i];
			if (Val == LookFor){
				Returnable = true;
				break;
			}
		}
		return Returnable;
	}
	
	void InsertInto(Key Insertable, Key In[CachedKeys]){
		for (uchar i = 0; i < CachedKeys; i++){
			if (In[i].IsNull()){
				In[i].Recreate(Insertable);
				break;
			}
		}
	}

	void ForceBootsel(){
		printf("Entered bootsel manually\n");
		gpio_put(PICO_DEFAULT_LED_PIN,1);
		reset_usb_boot(0,0);
	}

	Key Code = Key();

	void Scan(bool* const& Changed){
		NumKeysPressed = 0;
		uchar CurrXPos = 0;
		uchar CurrYPos = 0;

		for (uchar y : KeyboardInputs){
			CurrXPos = 0;

			gpio_put(y,0);
			sleep_us(15);
			
			for (uchar x : KeyboardOutputs){
				// Check if column is pressed in the current row
				bool Pressed = gpio_get(x) == 0;
				int KeyPos = 0;
				Code.Recreate(CurrXPos, CurrYPos);

				if (Pressed){
					// Instantly toss to bootsel mode
					if (Code.GetChar() == KeyUpgrade){
						ForceBootsel();
					}
					
					// Normal key procedure
					if (IsInKeyList(Code, KeysJustPressed, KeyPos)){

						KeysJustPressed[KeyPos].Nullify();
						InsertInto(Code,KeysPressing);
						// Key pressing

					} else if (!IsInKeyList(Code, KeysPressing)){

						// Key just got pressed
						InsertInto(Code,KeysJustPressed);
						*Changed = true;

					} else if (IsInKeyList(Code, KeysPressing)) {

						// Key pressing

					}
					NumKeysPressed++;
				} else if (IsInKeyList(Code, KeysPressing, KeyPos)){

					// Key released
					KeysPressing[KeyPos].Nullify();
					*Changed = true;

				} else if (IsInKeyList(Code, KeysJustPressed, KeyPos)){

					// Key released quite early
					KeysJustPressed[KeyPos].Nullify();
					*Changed = true;
				}

				KeysPressed[CurrYPos][CurrXPos] = Pressed;

				CurrXPos++;			
			}

			gpio_put(y,1);
			CurrYPos++;
		}
	}
	
//╚═══════════════════════════════ End of Key array functions ══════════════════════════════╝

// !SECTION Key array functions