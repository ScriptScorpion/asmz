***SimpleASM - utility for simpler assembler code compiltion***

# Disclaimer
* for tool to work you need: nasm(but you change to what you want), ld.

# Installation
1. Put "asm" command into `/usr/bin/`. If you want to compile code yourself(needed gcc or clang): `cd SimpleASM && cd src && g++ main.cpp -o asm`

# How Compile
1. if you putted tool into `/usr/bin` or `/usr/local/bin`, type: `asm "assembler file"`.

This tool right now only for Linux and BSD because i don't work on Windows

# Issues 
* if you want to get different output name specify name with flag -o, example: `asm example.asm -o exe.o`. `.o` is needed, else you get error.
