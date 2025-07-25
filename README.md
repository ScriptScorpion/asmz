***SimpleASM - utility for simpler assembler code compiltion***

# Disclaimer
* for tool to work you need: nasm, ld.

  This tool right now only for Linux and BSD systems.

# Installation
 **There are two ways to install: 1 - manual, 2 - automatic**

1. Put "asm" command into `/usr/local/bin/`. If you want to compile code yourself(needed gcc or clang): `cd SimpleASM && cd src && g++ main.cpp -o asm`.

2. Run `chmod +x INSTALL` and `sudo ./INSTALL`, or you can build code yourself with gcc or clang: `cd SimpleASM && cd src && g++ cmdinstall.cpp -o INSTALL && sudo ./INSTALL`.

# How Compile

1. if you putted tool into `/usr/local/bin`, type: `asm "assembler file"` change "assembler file" to name of assembler file you want to compile, or if you want specify name of output, type `-o` flag and name of executable with `.o` extension.

# Issues

* if you want to get different output name specify name with flag -o, example: `asm example.asm -o exe.o`. `.o` is needed, else you get error.
