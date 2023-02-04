#pragma once

#include "Character.h"
#include "CharacterSet.h"
#include <vector>
#include <string>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

struct not_digit {
    bool operator()(const char c) {
        return c != ' ' && !std::isdigit(c);
    }
};

class Parser {
    private:
        const static inline std::vector<std::string> elements = {"id", "x", "y", "width", "height", "xoffset", "yoffset", "xadvance", "page", "chnl"};
        static std::vector<int> get_line_data(std::string& input);

    public:
        static void parse(const std::string& filePath, std::unordered_map<int, Character>& characters);
};
