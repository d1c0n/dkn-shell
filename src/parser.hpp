#include <string>
#include <iostream>
#include <vector>
#include <sstream>

enum ParserState
{
    SPACE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
};

std::vector<std::string> parse(std::string const &text);
