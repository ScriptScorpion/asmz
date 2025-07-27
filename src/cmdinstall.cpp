#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <pwd.h>
#include <cstdlib>

std::string gethome() {
    if (const char *sudo_user = std::getenv("SUDO_USER")) {
        if (struct passwd* pwd = getpwnam(sudo_user)) {
            return pwd->pw_dir;
        }
    }
    
    if (const char *home = std::getenv("HOME")) {
        return home;
    }
    
    return "";
}

int main() {
    std::string home_dir = gethome();
    if (home_dir.empty()) {
        std::cout << "Error: Failed to determine home directory\n";
        return 1;
    }

    std::filesystem::path source = home_dir + "/Downloads/asmz/command/asmz";
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
