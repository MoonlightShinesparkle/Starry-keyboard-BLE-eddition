#pragma once

#define uchar unsigned char
#define CachedKeys 6

#include <Src/Util/Data.hpp>
#include <Src/Util/Events/Event.hpp>
#include <Src/Config/Physical.hpp>

// SECTION Key class

//╔════════════════════════════════════ Start of key class ════════════════════════════════════╗

	/// @brief Information container for keys
	class Key{
		protected:

		/// @brief Position within the button matrix
		CompactVec2 Position;

		/// @brief Defines key useability
		bool Viable = true;

		public:
		/**
		 * @brief Creates a prepositioned key
		 * @param X X position
		 * @param Y Y position
		 * @param Layout Current layout
		 */
		inline Key(uchar X, uchar Y, uchar Layout){
			Position = CompactVec2(X,Y);
		}

		/// @brief Creates a null key
		inline Key() : Key(0,0,0){
			Nullify();
		}

		/**
		 * @brief Returns the char equivalent of the key
		 * @return Char equivalent of the key
		 */
		uchar GetChar();

		/**
		 * @brief Returns key equivalence
		 * @param Eq Key to compare to
		 * @return Equivalence
		 * @note Null keys can't be equal to other keys
		 */
		inline bool operator ==(Key Eq){
			return !IsNull() && !Eq.IsNull() && (((uchar) Eq) == GetChar());
		}

		/// @brief Another access to GetChar()
		inline operator uchar(){
			return GetChar();
		}

		/// @brief Removes viability
		inline void Nullify(){
			Viable = false;
		}

		/**
		 * @brief Checks if the key has been nullified
		 * @return Key being null
		 */
		inline bool IsNull(){
			return !Viable;
		}

		/**
		 * @brief Regenerates key, giving a viability
		 * @param X X position in the keyboard
		 * @param Y Y position in the keyboard
		 * @param Layout Layout of the keyboard
		 */
		inline void Recreate(uchar X, uchar Y){
			Position.SetValues(X,Y);
			Viable = true;
		}

		/// @brief Copies another key's layout, giving a viability
		/// @param Other Key whose values will be copied
		inline void Recreate(Key Other){
			Recreate(Other.Position.GetX(),Other.Position.GetY());
		}
	};

//╚═════════════════════════════════════ End of key class ═════════════════════════════════════╝

// !SECTION Key class

// SECTION Keyboard

//╔═════════════════════════════════════ Start of keyboard ════════════════════════════════════╗

	/// Key char used to force bootsel onto the device, should not be sent as it's reserved
	const uchar KeyUpgrade = 0xE8;

	/**
	 * @brief A bidimensional array which holds the available layouts, 
	 * composed of the many keys loaded into the keyboard
	 * @note The default layout is as follows:
	 * @note M O N L I
	 * @note G H T W A
	 * @note S E R ; 3
	 * @note * O . = -
	 * @note Where * is bootsel
	 */
	static uchar LoadedLayout[SizeY][SizeX]{
		// Moonlight was here layout
		{0x10,0x12,0x11,0x0F,0x0C},
		{0x0A,0x0B,0x17,0x1A,0x04},
		{0x16,0x08,0x15,0x33,0x20},
		{0x2C,0x28,0xE1,0x39,0x2A},
		{KeyUpgrade,0x27,0x37,0x2E,0x2D}
	};

	/**
	 * @brief Obtains a key's char
	 * @return Key char or null character if null
	 */
	inline uchar Key::GetChar(){
		return IsNull()? '\0' : LoadedLayout[Position.GetY()][Position.GetX()];
	}

	/**
	 * @brief Adds pull up resistors to SetAsInput function
	 * @param GPIO 
	 */
	void SetKeyboardInput(uchar GPIO);

//║ *- Inpin & Outpin are keyboard based													   ║
//║ *- Based on the Moonlit calc project													   ║
//║	   KBD							 Pico													   ║
//║	 ╔═════╗						╔════╗													   ║
//║	 ╠═════╣			Inpin		║	 ║													   ║
//║	 ║	   ║ <┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ║	 ║													   ║
//║	 ║	   ║ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅> ║	 ║													   ║
//║	 ╚═════╝			Outpin		╚════╝													   ║
//║																							   ║

	/**
	 * @brief List of keyboard outputs (Outpins)
	 * @note Outpins are keyboard orientated; they send signals to the pico
	 */
	const uchar KeyboardOutputs[SizeX]{
		5,6,7,8,9
	};

	/**
	 * @brief List of keyboard inputs (Inpins)
	 * @note Inpins are keyboard orientated; they recieve signals from the pico
	 */
	const uchar KeyboardInputs[SizeY]{
		0,1,2,3,4
	};

	/// @brief Sets input and output pins to drive the keyboard
	void SetupKeys();

	/// @brief Map of pressed keys as booleans
	extern bool KeysPressed[SizeY][SizeX];

	/// @brief Number of keys currently pressed
	extern uchar NumKeysPressed;

	/// @brief Keys get added here when just pressed
	extern Key KeysJustPressed[CachedKeys];

	/// @brief Keys get added here when pressing
	extern Key KeysPressing[CachedKeys];

	/// @brief Scans through the keyboard to check for keys, updates them in all arrays/values
	void Scan(bool* const& Changed);

	/**
	 * @brief Checks if a key exists in an array of length CachedKeys
	 * @param LookFor Key to look for
	 * @param In Array to look into
	 * @param Position Position of LookFor in In or -1
	 * @return Existance of LookFor in In
	 */
	bool IsInKeyList(Key LookFor, Key In[CachedKeys], int &Position);
	 

	/**
	 * @brief Checks if a key exists in an array of length CachedKeys
	 * @param LookFor Key to look for
	 * @param In Array to look into
	 * @return Existance of LookFor in In
	 */
	bool IsInKeyList(Key LookFor, Key In[CachedKeys]);

	/**
	 * @brief Attempts to insert the given key into an array
	 * @param Insertable Key to insert
	 * @param In List to insert into
	 */
	void InsertInto(Key Insertable, Key In[CachedKeys]);

	/// @brief Forces the pico to enter bootsel mode without requiring pressing "BOOTSEL"
	void ForceBootsel();

//╚══════════════════════════════════════ End of keyboard ═════════════════════════════════════╝

// !SECTION Keyboard