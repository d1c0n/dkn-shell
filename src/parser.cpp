
#include "parser.hpp"

std::vector<std::string> parse(std::string const &text)
{
    std::vector<std::string> tokens{};
    ParserState state{ParserState::SPACE};

    std::string currentToken{""};

    bool escape{false};
    bool escapeDouble{false};
    bool quotedExecutable{false};
    bool doubleQuotedExecutable{false};

    int counter{0};

    for (char c : text)
    {
        if (tokens.size() == 0 and !quotedExecutable and !doubleQuotedExecutable)
        {
            if (c == '\'')
            {
                // currentToken += c;
                quotedExecutable = true;
                state = ParserState::SINGLE_QUOTE;
                continue;
            }
            else if (c == '\"')
            {
                // currentToken += c;
                doubleQuotedExecutable = true;
                state = ParserState::DOUBLE_QUOTE;
                continue;
            }
        }
        if (escape)
        {
            currentToken += c;
            escape = false;
        }
        else if (escapeDouble)
        {
            if (c == '\\' or c == '$' or c == '\"' or c == '\n')
            {
                currentToken += c;
                escapeDouble = false;
            }
            else
            {
                currentToken += '\\';
                currentToken += c;
                escapeDouble = false;
            }
        }
        else if (c == '\\')
        {
            escape = true;

            if (state == ParserState::SINGLE_QUOTE)
            {
                currentToken += c;
                escape = false;
            }
            else if (state == ParserState::DOUBLE_QUOTE)
            {
                escape = false;
                escapeDouble = true;
            }
        }
        else if (state == ParserState::SINGLE_QUOTE)
        {
            if (c == '\'')
            {
                if (quotedExecutable)
                {
                    // currentToken += c;
                    tokens.push_back(currentToken);
                    currentToken.clear();
                    quotedExecutable = false;
                }
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
                if (doubleQuotedExecutable)
                {
                    // currentToken += c;
                    tokens.push_back(currentToken);
                    currentToken.clear();
                    doubleQuotedExecutable = false;
                }
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
        counter++;
    }

    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}