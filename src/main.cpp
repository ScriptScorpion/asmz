#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>

#if __unix__
    const std::string OS =  "-f elf64 ";
#else 
    throw std::runtime_error("Unsupported OS");
#endif

std::string removextension(const std::string &filename) {
    size_t lastDot = filename.find_last_of('.');
    if (lastDot != std::string::npos) {
        return filename.substr(0, lastDot);
    }
    return filename; 
}

bool ishavextension(const std::string &name) {
    std::filesystem::path p(name);
    return p.has_extension();
}

std::string Findvector(const std::vector<std::string>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == "-o") {
            if (i + 1 < vec.size()) {  
                return vec[i + 1];     
            } else {
                return "";  
            }
        }
    }
    return "";  
}


int main(int argc, char *argv[]) {
    
    const std::string compiler = "nasm "; // change to your ASM compiler if it is GAS remove 8-12 lines
    std::string arguments = compiler + OS;
    std::string linker= "ld "; 
    std::string exestr = "./";
    std::vector <std::string> safeargc(argv, argv + argc);
    std::string Vec_extrac = Findvector(safeargc);  // gets file that specified by -o for vectors
    if (argc == 1) {
        std::cout << "Specify assembler file \n";
        std::exit(1);
    }
    for (int i = 1; i < argc; ++i) {   
        if (safeargc[i] == "-o") {
            if (!(Vec_extrac.empty()) && argc == 4) {
                safeargc[3] += ".o";
            }
            else if (!(Vec_extrac.empty()) && argc > 4) {
                break;
                std::cout << "Sorry, you cannot have more then 4 arguments(I will fix this in next updates)";
            }
        }
        arguments += safeargc[i];
        arguments += " ";
    }

    int ASMoutcome = system(arguments.c_str());
    if (ASMoutcome != 0) {
        std::cout << "Compiling error \n";
        std::exit(1);
    }
    if (Vec_extrac.empty()) {
        Vec_extrac = argv[1];
    }
    Vec_extrac = removextension(Vec_extrac);

    linker += Vec_extrac;
    linker += ".o ";
    linker += "-o "; 
    linker += Vec_extrac;
    
    int Oresult = system(linker.c_str());
    if (Oresult != 0) {
        std::cout << "Linking Error \n";
        std::exit(1);
    }

    exestr += Vec_extrac;
    int exeresult = system(exestr.c_str());
    if (exeresult != 0) {
        std::cout << "Execution error \n";
        std::exit(1);
    }
    return 0;
}
