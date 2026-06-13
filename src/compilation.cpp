#include <iostream>
#include <cstdlib>
#include "compilation.hpp"

bool Parser::Compile(const std::string &arguments, const std::string &link_arguments, const std::string &output) {
    std::string exe_str;
    exe_str = arguments + " -o " + output + ".o";
    if (system(exe_str.c_str()) != 0) {
        std::cerr << "\nCompilation error!\n";
        return false;
    }
    exe_str = link_arguments + output + ".o -o " + output;
    if (system(exe_str.c_str()) != 0) {
        std::cerr << "\nLinking error!\n";
        return false;
    }
    exe_str = "rm " + output + ".o";
    if (system(exe_str.c_str()) != 0) {
        std::cerr << "\nDeletion error!\n";
        return false;
    }
    std::cout << "Compilation Finished Successfully\n";
    return true;
}
