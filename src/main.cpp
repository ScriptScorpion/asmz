#include <filesystem>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "all.hpp"

#if defined(__unix__) || defined(unix)
    const std::string OS = "-f elf64 ";
#else 
    throw std::runtime_error("Unsupported OS");
#endif

std::string remove_extension(const std::string &filename) {
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


std::string CheckCompilers() {
    std::string answer = "";

    const std::vector<std::pair<std::string, std::string>> compilers = {
        {"   GAS", "as --version > /dev/null 2>&1"},
        {"   NASM", "nasm --version > /dev/null 2>&1"},
        {"   YASM", "yasm --version > /dev/null 2>&1"},
        {"   FASM", "fasm --version > /dev/null 2>&1"}
    };

    for (const auto &[name, cmd] : compilers) {
        if (std::system(cmd.c_str()) == 0) {
            answer += name + "\n";
        }
    }
    return answer;
}

int main(int argc, char *argv[]) {
    Parser instance;
    std::vector <std::string> Compilers = {"nasm", "as", "yasm"};
    std::string arguments = "";
    std::ifstream Code;
    std::string line;
    std::string ExtraLD = "";
    std::vector <std::string> safeargc(argv, argc + argv);
    std::string Vec_extrac = Findvector(safeargc);  // gets file that specified by -o for vectors
    bool is_gas = false;
    const std::string availableCompilers = CheckCompilers();
    if (argc < 2) {
        std::cerr << "Type 'asmz -h' for more help \n";
        return 1;
    }
    else if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            if (!availableCompilers.empty()) { 
                std::cout << 
                "ASMZ 1.6 \n"
                "Usage: asmz (ASM-Compiler) {ASM_FILE} \n\n"
                "(ASM-Compiler) - is Assembly compiler you want to use, see below all avaible compilers \n"
                "{ASM_FILE} - is code written in Assembly language that you want to compile \n\n"
                "Flags: \n"
                "   -o: Will make executable name to what you typed after this flag \n"
                "Avaible Assembly compilers: \n" << availableCompilers;
                return 0;
            }
            else {
                std::cerr << "Install Assembly language compiler first, like: nasm, as, yasm. \n";
                return 1;
            }
        }
        else {
            std::cerr << "Specify Assembly compiler you are want to use, and assembly file to compile. type 'asmz -h' for more help \n";
            return 1;
        }
    }
    else {
        const std::filesystem::path asm_file = argv[2];
        if (!std::filesystem::exists(asm_file) || (asm_file.extension() != ".s" && asm_file.extension() != ".S" && asm_file.extension() != ".asm")) {
            std::cerr << "Specify assembly file to compile. type 'asmz -h' for more help \n";
            return 1;
        }
    }
    if (Vec_extrac.find_first_of(";&|<>!*%^()$`/{}") != std::string::npos) {
        std::cerr << "Error: invalid symbols.\n";
        return 1;
    }
    Code.open(argv[2]);
    for (std::string x : Compilers) {
        if (argv[1] == Compilers[0]) {
            arguments = "nasm ";
            while (std::getline(Code, line))
            {
                if ((line.find("bits 32")) != std::string::npos) {
                    arguments += "-f elf32 ";
                    ExtraLD = "-m elf_i386 ";
                    break;
                }
                else {
                    arguments += OS;
                    break;
                }
            }
            break;
        }
        else if (argv[1] == Compilers[1] || std::string(argv[1]) == "gas") {
            is_gas = true;
            arguments = "as ";
            break;
        }
        else if (argv[1] == Compilers[2]) {
            arguments = "yasm ";
            while (std::getline(Code, line))
            {
                if ((line.find("bits 32")) != std::string::npos) {
                    arguments += "-f elf32 ";
                    ExtraLD = "-m elf_i386 ";
                    break;
                }
                else {
                    arguments += OS;
                    break;
                }
            }
            break;
        }
        else {
            std::cerr << "Unsupported compiler\n";
            return 1;
        }
    }
    Code.close();
    if (is_gas && Vec_extrac.empty()) {
        safeargc.insert(safeargc.begin() + 3, "-o");
        safeargc.insert(safeargc.begin() + 4, (remove_extension(std::string(argv[2]))) + ".o");
    }
    for (size_t i = 2; i < safeargc.size(); ++i) {
        if (safeargc[i] == "-o") {
            if (!Vec_extrac.empty()) {
                safeargc[i+1] += ".o";
            }
        }
        arguments += safeargc[i];
        arguments += " ";
    }
    arguments += "-g";
    if (Vec_extrac.empty()) {
        Vec_extrac = remove_extension(argv[2]);   
    }
    if (instance.Compile(arguments, ExtraLD, remove_extension(Vec_extrac)) == false) {
        std::cerr << instance.error << std::endl;
        return -1;
    }
    
    return 0;
}
