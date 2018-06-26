# CHIP-8-emu

Another CHIP-8 emulator, this time in C++.
The goal of this project is to provide a stable and robustly-featured CHIP-8 emulator with good performance.

## How to run

Currently to run the emulator, you need to invoke it from the command line.
You can either drag your ROMs beside the application and invoke like so.<br />
*"chip8 [ROM]"*<br />
Or if your folder structure is similar to the source's, or something like this:

*/chip-8-emu* <br />
*--/bin*<br />
*------/chip8.exe* <br />
*--/roms* <br />
*------/pong* <br />

Then you can invoke chip8 like so, <br />
*"chip8 ../[path to ROM]"* <br />

"../" Will take you up a directory, and from there the path to the ROM can be specified. 

## How to play

CHIP-8 has a hexidecimal keypad, meaning it as 16 keys that look like so; </br>

1 2 3 C </br>
4 5 6 D </br>
7 8 9 E </br>
A 0 B F </br>

For now, these keys have been mapped to this; </br>

1 2 3 4 </br>
Q W E R </br> 
A S D F </br>
Z X C V </br>

In the future, we may add rebindable keys, however I for the life of me could not find a more sensible place to bind these.</br>

