ASMZ (Eazy ASM), a utility for simpler Assembly code compilation
===================================================================
**ASMZ** helps compile Assembly code as FASM(immediately making file executable), but using NASM or others Assembly compilers. 

# Requirements
  * `g++` or `clang++`
  * `make`
  * **assembly compiler** (check out wiki for more info about this: [Compilers](https://github.com/ScriptScorpion/asmz/wiki/Assembly-Compilers))

# Disclaimer
  **ASMZ** right now only for Linux and BSD systems. But you there are ways to get it for Windows, here is possible ways: [Click here](https://github.com/ScriptScorpion/asmz/wiki/ASMZ-for-Windows)

# Installation

1. Enter project directory and run: `sudo make install` this will let run program from any directory you are in.

2. If you don't wanna have option to run program from any directory you can type `make compile` instead.

# How Compile Assembly code

1. Type: `asmz {Assembly-language compiler} "assembler file"` change "assembler file" to name of assembler file you want to compile, change "Assembly-language compiler" to your assembler compiler. If you want specify name of output, type `-o` flag, and after flag type name of executable you want.

# Issues

* no issues for now (if you found issue describe it in [Issues](https://github.com/ScriptScorpion/asmz/issues) page).
