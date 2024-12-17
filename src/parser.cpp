
#include "parser.hpp"

std::vector<std::string> parse(std::string const &text)
{
    std::vector<std::string> tokens{};
    ParserState state{ParserState::SPACE};

    std::string currentToken{""};

    bool escape{false};

    for (char c : text)
    {
        if (escape)
        {
            currentToken += c;
        }
        else if (c == '\\')
        {
            escape = true;

            if (state == ParserState::SINGLE_QUOTE)
            {
                currentToken += c;
                escape = false;
            }
        }
        else if (state == ParserState::SINGLE_QUOTE)
        {
            if (c == '\'')
            {
                state = ParserState::SPACE;
            }
            else
            {
                currentToken += c;
            }
        }
        else if (state == ParserState::DOUBLE_QUOTE)
        {
            if (c == '\"')
            {
                state = ParserState::SPACE;
            }
            else
            {
                currentToken += c;
            }
        }
        else // NORMAL STATE
        {
            if (c == '\'')
            {
                state = ParserState::SINGLE_QUOTE;
            }
            else if (c == '\"')
            {
                state = ParserState::DOUBLE_QUOTE;
            }
            else if (std::isspace(c))
            {
                if (!currentToken.empty())
                {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            }
            else
            {
                currentToken += c;
            }
        }
    }

    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}