#include "all.hpp"
bool Parser::Compile(const std::string arguments, const std::string ExtraLD, const std::string output) {
    std::string exe_str;
    if (system(arguments.c_str()) != 0) {
        error = "\nCompilation error!\n";
        return false;
    }
    exe_str = "ld " + ExtraLD + " " + (output + ".o") + " -o " + output;
    if (system(exe_str.c_str()) != 0) {
        error = "\nLinking error!\n";
        return false;
    }
    exe_str = "rm " + output + ".o";
    if (system(exe_str.c_str()) != 0) {
        error = "\nDeletion error!\n";
        return false;
    }
    exe_str = "./" + output;
    if (system(exe_str.c_str()) != 0) {
        error = "\nExecution error!\n";
        return false;
    }
    return true;
}
