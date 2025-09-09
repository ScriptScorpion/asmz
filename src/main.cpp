#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

#if defined(__unix__) || defined(unix)
    const std::string OS = "-f elf64 ";
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


std::string CheckCompilers() {
    std::string answer = "";

    const std::vector<std::pair<std::string, std::string>> compilers = {
        {"   GAS", "as --version > /dev/null 2>&1"},
        {"   NASM", "nasm --version > /dev/null 2>&1"},
        {"   YASM", "yasm --version > /dev/null 2>&1"},
        {"   FASM (Not supported)", "fasm --version > /dev/null 2>&1"}
    };

    for (const auto& [name, cmd] : compilers) {
        if (std::system(cmd.c_str()) == 0) {
            answer += name + "\n";
        }
    }
    return answer;
}

int main(int argc, char *argv[]) {
    std::vector <std::string> Compilers = {"nasm", "as", "yasm"};
    std::string compiler = "";
    std::string arguments = "";
    std::string linker= "ld "; 
    std::string exestr = "./";
    std::string remover = "rm ";
    std::ifstream CodeArch;
    std::string line;
    std::string extraLd = "";
    std::string FileOpen;
    std::vector <std::string> safeargc(argv, argv + argc);
    std::string Vec_extrac = Findvector(safeargc);  // gets file that specified by -o for vectors
    bool is_gas = false;
    const std::string availableCompilers = CheckCompilers();
    if (argc < 2) {
        std::cerr << "Specify Assembly compiler you are want to use (nasm, as, yasm). type 'asmz -h' for more help \n";
        std::exit(1);
        return 1;
    }
    else if (argc == 2 && std::string(argv[1]) != "-h") {
        std::cerr << "Specify Assembly file to compile.\n";
        std::exit(1);
        return 1;
    }
    if (Vec_extrac.find_first_of(";&|<>!*%^()$`/{}") != std::string::npos) {
        std::cerr << "Error: invalid symbols.\n";
        return 1;
    }
    for (int j = 1; j < argc; j++) {
        if (std::string(argv[j]) == "-h") { 
            std::cout << " ASMZ 1.3 \n"
            "Usage: asmz (ASM-Compiler) {EXAMPLE.asm} \n"
            "(ASM-Compiler) - is Assembly compiler you want to use, see below all avaible compilers \n"
            "{EXAMPLE.asm} - is code written in Assembly language that you want to compile \n"
            "\n"
            "Flags: \n"
            "   -o: Will make executable name to what you typed after this flag \n"
            "Avaible Assembly compilers: \n" << availableCompilers;
            return 0;
        }
        else if (availableCompilers.empty()) {
            std::cerr << "Install Assembly language compiler first, like: nasm, as, yasm. \n";
            return 1;
        }
    }
    FileOpen = argv[2];
    CodeArch.open(FileOpen);
    for (auto x : Compilers) {
        if (argv[1] == Compilers[0]) {
            compiler = "nasm ";
            arguments = compiler;
            while (std::getline(CodeArch, line))
            {
                if ((line.find("bits 32")) != std::string::npos) {
                    arguments += "-f elf32 ";
                    extraLd = "-m elf_i386 ";
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
            compiler = "as ";
            is_gas = true;
            arguments = compiler;
            break;
        }
        else if (argv[1] == Compilers[2]) {
            compiler = "yasm ";
            arguments = compiler;
            while (std::getline(CodeArch, line))
            {
                if ((line.find("bits 32")) != std::string::npos) {
                    arguments += "-f elf32 ";
                    extraLd = "-m elf_i386 ";
                    break;
                }
                else {
                    arguments += OS;
                    break;
                }
            }
            break;
        }
    }
    CodeArch.close();
    if (is_gas && !(Vec_extrac.empty())) {
        safeargc.insert(safeargc.begin() + 3, "-o");
        safeargc.insert(safeargc.begin() + 4, (removextension(std::string(argv[2]))) + ".o");
    }
    for (int i = 2; i < safeargc.size(); ++i) {
        if (safeargc[i] == "-o") {
            if (!(Vec_extrac.empty()) && argc == 5) {
                safeargc[4] += ".o";
            }
        }
        arguments += safeargc[i];
        arguments += " ";
    }
    int ASMoutcome = system(arguments.c_str());
    if (ASMoutcome != 0) {
        std::cerr << "Compiling error \n";
        std::exit(1);
    }
    if (Vec_extrac.empty()) {
        Vec_extrac = argv[2];   
    }
    Vec_extrac = removextension(Vec_extrac);
    linker += extraLd;
    linker += Vec_extrac;
    linker += ".o ";
    linker += "-o "; 
    linker += Vec_extrac;
    int Oresult = system(linker.c_str());
    if (Oresult != 0) {
        std::cerr << "Linking Error \n";
        std::exit(1);
    }
    remover += Vec_extrac + ".o";
    system(remover.c_str());
    exestr += Vec_extrac;
    int exeresult = system(exestr.c_str());
    if (exeresult != 0) {
        std::cerr << "Execution error \n";
        std::exit(1);
    }
    return 0;
}
