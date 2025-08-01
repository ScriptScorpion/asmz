ASMZ (Eazy ASM), a utility for simpler Assembly code compilation
===================================================================
**ASMZ** helps compile Assembly code as FASM(immediately making file executable), but using NASM or others Assembly compilers. 

# Disclaimer
* for **ASMZ** to work you need: **any Assembly compiler** (checkout Wiki for more info about supported compilers: [Compilers](https://github.com/ScriptScorpion/asmz/wiki/Assembly-Compilers) ), **ld** (checkout Wiki for more info: [Linkers](https://github.com/ScriptScorpion/asmz/wiki/Assembly-Language-Linkers) ).

  **ASMZ** right now only for Linux and BSD systems. But you there are ways to get it for Windows, here is possible ways: [Click here](https://github.com/ScriptScorpion/asmz/wiki/ASMZ-for-Windows)

# Installation
 **There are two ways to install: 1 - manual, 2 - automatic**

1. Put "asmz" command into `/usr/local/bin/`. If you want to compile code yourself(needed gcc or clang): `cd asmz && cd src && g++ main.cpp -o asmz`.

2. Run `chmod +x INSTALL` and `sudo ./INSTALL`, or you can build code yourself with gcc or clang: `cd asmz && cd src && g++ cmdinstall.cpp -o INSTALL && sudo ./INSTALL`.

# How Compile Assembly code

1. if you putted "asmz" into `/usr/local/bin`, type: `asmz {Assembly-language compiler} "assembler file"` change "assembler file" to name of assembler file you want to compile, change "Assembly-language compiler" to your assembler compiler. If you want specify name of output, type `-o` flag, and after flag type name of executable you want.

# Issues

* no issues for now (if you found issue describe it in [Issues](https://github.com/ScriptScorpion/asmz/issues) page).
