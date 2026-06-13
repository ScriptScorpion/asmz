#pragma once
#include <string>
class Parser {
    public:
        bool Compile(const std::string &arguments, const std::string &link_arguments, const std::string &output);
};
