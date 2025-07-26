***BASM (Better ASM) - a utility for simpler assembler code compiltion*** that helps compile Assembly code as FASM(immediately making file executable), but using NASM or others Assembly compilers. 

# Disclaimer
* for **BASM** to work you need: nasm, ld.

  **BASM** right now only for Linux and BSD systems.

# Installation
 **There are two ways to install: 1 - manual, 2 - automatic**

1. Put "asm" command into `/usr/local/bin/`. If you want to compile code yourself(needed gcc or clang): `cd SimpleASM && cd src && g++ main.cpp -o basm`.

2. Run `chmod +x INSTALL` and `sudo ./INSTALL`, or you can build code yourself with gcc or clang: `cd SimpleASM && cd src && g++ cmdinstall.cpp -o INSTALL && sudo ./INSTALL`.

# How Compile

1. if you putted **BASM** into `/usr/local/bin`, type: `basm "assembler file"` change "assembler file" to name of assembler file you want to compile, or if you want specify name of output, type `-o` flag and name of executable with `.o` extension.

# Issues

* if you want to get different output name specify name with flag -o, example: `basm example.asm -o exe.o`. `.o` is needed, else you get error.
