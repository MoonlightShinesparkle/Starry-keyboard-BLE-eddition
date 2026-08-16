#include "24C16.hpp"

// SECTION Chip class

//╔═════════════════════════════════════════════════ Start of Chip class ═══════════════════════════════════════════════╗

	Mem24C16::Mem24C16(unsigned const char Data, unsigned const char Clock, i2c_inst_t* I2CBus){
        UseableI2CBus = I2CBus;
        SDAPin = Data;
        SCLPin = Clock;

        i2c_init(I2CBus, 100000);

        InitPins();
    }

    void Mem24C16::InitPins(){
        gpio_set_function(SDAPin, GPIO_FUNC_I2C);
        gpio_set_function(SCLPin, GPIO_FUNC_I2C);

        gpio_pull_up(SDAPin);
        gpio_pull_up(SCLPin);
    }

    void Mem24C16::ParseAddress(unsigned int Target, unsigned char* Address, unsigned char* Offset){
        *Address = BaseAddress | (unsigned char)(Target/BlockSize);
        *Offset = (unsigned char)(Target%BlockSize);
    }

    unsigned char Mem24C16::GetValue(unsigned int Target){
        unsigned char Addr;
        unsigned char Offs;

        if (Target >= Length){
            Target = Length -1;
        }

        ParseAddress(Target, &Addr, &Offs);
        
        i2c_write_blocking(UseableI2CBus, Addr, &Offs, 1, true);
        i2c_read_blocking(UseableI2CBus, Addr, SingleByteBuffer, 1, false);

        return SingleByteBuffer[0];
    }

    void Mem24C16::SetValue(unsigned int Target, unsigned char Value){
        unsigned char Addr;
        unsigned char Offs;

        ParseAddress(Target, &Addr, &Offs);

        unsigned char Data[2] = {Offs, Value};

        i2c_write_blocking(UseableI2CBus, Addr, Data, 2, false);

        Delay();
    }

//╚═════════════════════════════════════════════════ End of Chip class ═════════════════════════════════════════════════╝

// !SECTION Chip class