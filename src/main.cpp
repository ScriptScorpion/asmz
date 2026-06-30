#include <iostream>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include "compilation.hpp"

#if !defined(__unix__) && !defined(unix) && !defined(__unix)
    throw std::runtime_error("Unsupported OS");
#endif

std::string remove_extension(const std::string &filename) {
    size_t lastDot = filename.find_first_of('.');
    if (lastDot != std::string::npos) {
        return filename.substr(0, lastDot);
    }
    return filename; 
}
std::string remove_path(const std::string &path) {
    if (path.find_last_of("\\/") != std::string::npos) {
        return path.substr(path.find_last_of("\\/")+1, path.size());
    }
    return path;
}

std::string CheckCompilers() {
    std::string answer = "";

    const std::vector<std::pair<std::string, std::string>> compilers = {
        {"\tGAS", "command -v as > /dev/null 2>&1"},
        {"\tNASM", "command -v nasm > /dev/null 2>&1"},
        {"\tYASM", "command -v yasm > /dev/null 2>&1"},
        {"\tFASM", "command -v fasm > /dev/null 2>&1"}
    };

    for (const auto &[name, cmd] : compilers) {
        if (system(cmd.c_str()) == 0) {
            answer += name + "\n";
        }
    }
    return answer;
}

int main(int argc, char *argv[]) {
    Parser instance;
    std::string arguments = "";
    std::string output_file = "";
    std::string input_file = "";
    std::string line = "";
    std::string linker_str = "ld";
    bool is_gas = false;
    bool is_nasm = false;
    bool is_yasm = false;
    bool is_x64 = true;
    bool is_x32 = false;
    bool debug_info = false;
    const std::string availableCompilers = CheckCompilers();
    
    if (argc < 2 || argc > 12) {
        std::cerr << "Type 'asmz -h' for more help \n";
        return 1;
    }
    for (size_t i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            if (!availableCompilers.empty()) { 
                std::cout << 
                "ASMZ 1.8 \n"
                "Usage: asmz (Options) {ASM_FILE} \n\n"
                "{ASM_FILE} - is code written in Assembly language that you want to compile \n\n"
                "Flags: \n"
                "\t-N: Use NASM assembler\n"
                "\t-Y: Use YASM assembler\n"
                "\t-G: Use GAS assembler\n"
                "\t--ld: Use LD linker(default)\n"
                "\t--lld: Use LLD linker\n"
                "\t--64: Generate code for the x64 CPU(default)\n"
                "\t--32: Generate code for the x32 CPU\n"
                "\t-o: Specify executable name\n"
                "\t-d: Add debug information to the file\n"
                "Avaible Assembly compilers: \n" << availableCompilers;
                return 0;
            }
            else {
                std::cerr << "You need to install Assembly language compiler to continue. Type 'asmz -h' for more help.\n";
                return 1;
            }
        }
        else if (strcmp(argv[i], "-N") == 0) {
            is_nasm = true;
        }
        else if (strcmp(argv[i], "-Y") == 0) {
            is_yasm = true;
        }
        else if (strcmp(argv[i], "-G") == 0) {
            is_gas = true;
        }
        else if (strcmp(argv[i], "--ld") == 0) {
            linker_str = "ld";
        }
        else if (strcmp(argv[i], "--lld") == 0) {
            linker_str = "ld.lld";
        }
        else if (strcmp(argv[i], "--64") == 0) {
            is_x64 = true;
            is_x32 = false;
        }
        else if (strcmp(argv[i], "--32") == 0) {
            is_x32 = true;
            is_x64 = false;
        }
        else if (strcmp(argv[i], "-d") == 0) {
            debug_info = true;
        }
        else if (strcmp(argv[i], "-o") == 0 && ((i+1) < argc)) {
            output_file = argv[i+1];
            i++;
        }
        else {
            const std::filesystem::path asm_file = argv[i];
            if (!std::filesystem::exists(asm_file) || (asm_file.extension() != ".s" && asm_file.extension() != ".S" && asm_file.extension() != ".asm")) {
                std::cerr << "You need to specify correct assembly file to compile. Type 'asmz -h' for more help.\n";
                return 1;
            }
            input_file = argv[i];

        }
    }
    
    if (input_file.empty()) {
        std::cerr << "Error: input filename is not specified.\n";
        return 1;
    }
    if (output_file.empty()) {
        output_file = remove_path(remove_extension(input_file));
    }
    if (input_file.find_first_of(";&|<>!*%^()$`{}") != std::string::npos || output_file.find_first_of(";&|<>!*%^()$`{}") != std::string::npos) {
        std::cerr << "Error: invalid symbols in filename.\n";
        return 1;
    }
    
    if (is_nasm) { 
        arguments = "nasm";
        if (is_x32) {
            arguments += " -f elf32 ";
            linker_str += " -m elf_i386";
        }
        else {
            arguments += " -f elf64 ";
            linker_str += " -m elf_x86_64";
        }
        if (debug_info) {
            arguments += "-g ";
        }
    }
    else if (is_gas) {
        arguments = "as";
        if (is_x32) {
            arguments += " --32 ";
            linker_str += " -m elf_i386";
        }
        else {
            arguments += " --64 ";
            linker_str += " -m elf_x86_64";
        }
        if (debug_info) {
            arguments += "-g ";
        }
    }
    else if (is_yasm) {
        arguments = "yasm";
        if (is_x32) {
            arguments += " -f elf32 ";
            linker_str += " -m elf_i386";
        }
        else {
            arguments += " -f elf64 ";
            linker_str += " -m elf_x86_64";
        }
        if (debug_info) {
            std::cerr << "Sorry, but 'yasm' doesn't have option to include debugging info.\n";
            return 1;
        }
    }
    else {
        std::cerr << "You need to specify atleast one assembler to use.\n";
        return 1;
    }
    arguments += input_file;
    linker_str += ' ';
    
    if (instance.Compile(arguments, linker_str, output_file) == false) {
        return 1;
    }
    
    return 0;
}
