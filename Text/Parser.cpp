#include "Parser.h"

void Parser::parse(const std::string &filePath, std::unordered_map<int, Character>& characters) {
    auto numregex = [](const std::string&  item) { return item + R"(="(\d*)" ")"; };

    std::ifstream file(filePath);
    std::string s;

    // skip first few lines
    for (int i = 0; i < 3; i++) getline(file, s);

    getline(file, s);

    auto nums = get_line_data(s);
    int numchars = nums[0];

    for (int i = 0; i < numchars; i++) {
        getline(file, s);
        auto nums = get_line_data(s);

        Character glyph_char = {
                nums[0],
                static_cast<double>(nums[1]),
                static_cast<double>(nums[2]),
                static_cast<double>(nums[3]),
                static_cast<double>(nums[4]),
                static_cast<double>(nums[5]),
                static_cast<double>(nums[6]),
                static_cast<double>(nums[7])
        };
        characters.insert({nums[0], glyph_char});

    }
}
std::vector<int> Parser::get_line_data(std::string &input) {
    not_digit not_a_digit;
    std::string::iterator end = std::remove_if(input.begin(), input.end(), not_a_digit);
    std::string all_numbers(input.begin(), end);

    std::stringstream ss(all_numbers);
    std::vector<int> numbers;

    for(int i = 0; ss >> i; ) {
        numbers.push_back(i);
    }

    return numbers;
}
