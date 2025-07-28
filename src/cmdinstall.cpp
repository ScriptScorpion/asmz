/*

This file helps install "asmz" command to /usr/local/bin/ you can do that yourself if you want

*/
#include <iostream>
#include <filesystem>
#include <pwd.h>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <string>

std::string getExecutableDir() {
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1); 
    if (len != -1) {
        buffer[len] = '\0';
        std::string::size_type pos = std::string(buffer).find_last_of("/");
        return std::string(buffer).substr(0, pos);
    }   
    return ""; 
}

std::string findAsmz(const std::filesystem::path& directory) {
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().filename() == "asmz") {
                return entry.path();
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return "";
}

int main() {
    std::string exe = getExecutableDir();
    if (exe.empty()) {
        std::cout << "Error: Failed to executable directory\n";
        return 1;
    }

    std::filesystem::path source = findAsmz(exe);
    std::filesystem::path destination = "/usr/local/bin/asmz";

    if (!std::filesystem::exists(source)) {
        std::cout << "Error: Source file not found\n";
        return 1;
    }

    try {
        std::filesystem::copy(source, destination);
        std::cout << "Installed successfully\n";
    } 
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        if (e.code() == std::errc::permission_denied) {
            std::cerr << "Try running with sudo\n";
        }
        return 1;
    }

    return 0;
}
