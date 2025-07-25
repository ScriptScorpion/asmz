#include <iostream>
#include <filesystem>
#include <cstdlib> 

int main() {
    std::string home = std::getenv("HOME");
    std::filesystem::path source = home + "/Downloads/SimpleASM/command/asm";
    std::filesystem::path destination = "/usr/local/bin/asm";
    try {
        if (!std::filesystem::exists(source)) {
            std::cout << "Error: File not found " + std::string(source) << std::endl;
            return 1;
        }
        std::filesystem::copy(source, destination); 
//        std::filesystem::remove(source);
        std::cout << "Installation complete!";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
