#pragma once

#include "pico/stdlib.h"
#include <stdio.h>
#include <string>

#define println(str) printf("%s\n",str)

// SECTION - GPIO definitions

//╔═════════════════════════ Start of GPIO definitions ═════════════════════════╗

    /**
	 * @brief Turns a GPIO into an output pin
	 * @param GPIO GPIO to set
     */
    void SetAsOutput(uint GPIO);

    /**
     * @brief Turns a GPIO into an input pin
	 * @param GPIO GPIO to set
	 * @param PullDown Use pull down resistor
     */
    void SetAsInput(uint GPIO, bool PullDown);

//╚══════════════════════════ End of GPIO definitions ══════════════════════════╝

// !SECTION - GPIO definitions

// SECTION - CompactVec2 definitions

//╔═════════════════════ Start of CompactVec2 definitions ══════════════════════╗

    /// @brief Class capable of storing an X and Y coordinate in a single byte
    class CompactVec2{
        private:
        /// @brief Internal unsigned char that holds the components
        unsigned char Value;

        public:
        /**
         * @brief Get the X component
	     * @return X component
         */
        unsigned char GetX();

        /**        
         * @brief Get the Y component
	     * @return Y component
         */
        unsigned char GetY();

        /**        
         * @brief Set X component of the value
	     * @param X X component
         */
        void SetX(unsigned char X);

        /**        
         * @brief Set Y component of the value
	     * @param Y Y component
         */
        void SetY(unsigned char Y);

        /**        
         * @brief Set both components of the value
	     * @param X X component
	     * @param Y Y component
         */
        void SetValues(unsigned char X, unsigned char Y);

        /**        
         * @brief Creates a Vector2 stored in a single byte
	     * @param X X component
	     * @param Y Y component
         */
        CompactVec2(unsigned char X, unsigned char Y);

        /// @brief Creates an empty CompactVec2
        inline CompactVec2() : CompactVec2(0,0){};
    };

//╚══════════════════════ End of CompactVec2 definitions ═══════════════════════╝

// !SECTION - CompactVec2 definitions