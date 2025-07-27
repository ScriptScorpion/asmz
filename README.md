***BASM (Better ASM) - a utility for simpler and better Assembly code compiltion***. **BASM** helps compile Assembly code as FASM(immediately making file executable), but using NASM or others Assembly compilers. 

# Disclaimer
* for **BASM** to work you need: nasm, ld.

  **BASM** right now only for Linux and BSD systems.

# Installation
 **There are two ways to install: 1 - manual, 2 - automatic**

1. Put "basm" command into `/usr/local/bin/`. If you want to compile code yourself(needed gcc or clang): `cd BASM && cd src && g++ main.cpp -o basm`.

2. Run `chmod +x INSTALL` and `sudo ./INSTALL`, or you can build code yourself with gcc or clang: `cd BASM && cd src && g++ cmdinstall.cpp -o INSTALL && sudo ./INSTALL`.

# How Compile Assembly code

1. if you putted **BASM** into `/usr/local/bin`, type: `basm "assembler file"` change "assembler file" to name of assembler file you want to compile, or if you want specify name of output, type `-o` flag, and after flag type name of executable you want.

# Issues

* no issues for now (if you found issue describe it in [Issues](https://github.com/ScriptScorpion/BASM/issues) page).
