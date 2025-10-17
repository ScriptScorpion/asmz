#pragma once
#include <string>
#include <cstdlib>
class Parser {
    public:
        std::string error;
    public:
        bool Compile(const std::string arguments, const std::string ExtraLD, const std::string output);
};
