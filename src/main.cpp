#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>

#if __unix__
    const std::string OS =  "-f elf64 ";
#else
    const std::string OS =  "-f win64 ";
#endif

// asm will be tool
std::string removextension(const std::string &filename) {
    size_t lastDot = filename.find_last_of('.');
    if (lastDot != std::string::npos) {
        return filename.substr(0, lastDot);
    }
    return filename; 
}

std::string Find(const std::string input) {
    size_t pos = 0;
    while (true) {
        pos = input.find("-o", pos);
        
        bool isStandalone = true;
        if (pos > 0 && !std::isspace(input[pos - 1])) {
            isStandalone = false;
        }

        if (isStandalone) {
            pos += 2;
            while (pos < input.size() && std::isspace(input[pos])) {
                pos++;
            }
            if (pos < input.size()) {
                return input.substr(pos);
            } else {
                return ""; 
            }
        } else {
            return "";
        }
    }
}


int main(int argc, char *argv[]) {

    std::string arguments = "nasm " + OS;
    std::string linker= "ld ";

     
    for (int i = 1; i < argc; ++i) {
        arguments += argv[i];
        arguments += " ";
    }
    std::cout << arguments << std::endl;
    std::string extrac = Find(arguments); // gets file that specified by -o
    if (extrac.empty()) {
        if (argc > 2) {
            std::cout << "Specify assembler file \n";
            std::exit(1);
        }
        else {
            extrac = argv[1];
        }
    }
    int ASMoutcome = system(arguments.c_str());
    if (ASMoutcome != 0) {
        std::cout << "Error \n";
        std::exit(1);
    }

    extrac = removextension(extrac);

    linker += extrac;
    linker += ".o ";
    linker += "-o "; 
    linker += extrac;

    int Oresult = system(linker.c_str());
    if (Oresult != 0) {
        std::cout << "Error \n";
        std::exit(1);
    }

    return 0;
}
