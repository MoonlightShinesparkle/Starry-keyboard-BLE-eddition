# Starry keyboard: BLE Edition
The starry keyboard recreated in C++ with some bluetooth implementation, it will allow for the use of a Li-Po battery to keep the unit
working unplugged

## Bluetooth implementation
Bluetooth capabilities were implemented through the study and recreation of a BTStack example along with a raspberry pico W example,
here's the main example used for the project:
- [HID keyboard demo](https://github.com/bluekitchen/btstack/blob/075a0780f0fad7ff67d58ac19f46e8953656a752/example/hid_keyboard_demo.c)

## NOTE
Project makes use of an in-progress board based on the original first iteration starry keyboard, it will include a battery charge 
and protection circuit along with a switch and a connection to ADC0 for battery voltage reading, as this board hasn't been
fabricated, this version is still not available

## Current capabilities
- Show as a bluetooth device
- Get connected to
- Show battery percent
- Send keys
- Use of modifier keys (such as shift)

## WIP capabilities
Being a work in progress version of the keyboard, some base starry keyboard capabilities are work in progress, due to the nature of
C++ (allowing deeper control of the pico W) 
- Key types (Normal, combo, text)
- EEPROM reading and key parsing
- Serial interface for key modifying
- LEDs lighting up in given cases (caps lock, num lock, scroll lock)

## Hopeful capabilities
- Fully proper bluetooth implementation

## Compilation of this project
Note: **project gives an error by default as it requires building for an essential file to be present**, building turns the gatt file
(present in Src/Descriptors) into a c file within the build directory that the project references, it is only essential to take this
in account if it's desired to modify the project

- Change the CMakeLists txt file to reflect the board used:
```CMake
set(PICO_BOARD pico2_w)
```
or
```CMake
set(PICO_BOARD pico_w)
```

### In MacOs
- Make use of the shell utilities on the root of the project: ReCMake, Build & Load
- In order to do so you may create a terminal window on the root of the project
- Run the ReCMake file, it will create a build directory or recreate the build directory from scratch if existent
- Run the Build file, it will run CMake's makefile and create the UF2 required for loading
- Run the Load file with your pico (2)W in bootsel mode plugged in, it will allow for loading and verifying the code
- You may press y to reboot the pico if the process was successful

### Otherwise
- Create an empty build directory, here CMake's files will be placed
- Make use of CMake to generate the build files
- Use make to begin the compilation process, if successful an UF2 file should be created
- Drag n' drop the UF2 file into the volume presented by your pico (2)W in bootsel mode
- The microcontroller should be 
