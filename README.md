# CHIP-8-emu

Another CHIP-8 emulator, this time in C++.
The goal of this project is to provide a stable and robustly-featured CHIP-8 emulator with good performance.

## Small speel about CHIP-8
*"To my surprise, there aren't many as many CHIP-8 emulator projects as I thought, though there is quite a few. The CHIP-8 platform is without a doubt obscure, but also super interesting to learn about, both for learning to write emulators, and giving one a healthy dose of interest in reverse engineering other platforms."    
-Sweets*

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
