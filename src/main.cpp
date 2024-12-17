#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "commands.hpp"
#include "parser.hpp"

void print_prompt()
{
  std::cout << "$ ";
}

std::vector<std::string> split(std::string const &text, char delimiter)
{
  std::vector<std::string> tokens{};
  std::string token{};

  std::istringstream sst{text};

  while (std::getline(sst, token, delimiter))
  {
    tokens.push_back(token);
  }

  return tokens;
}

int main()
{

  Commands commands;

  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  print_prompt();

  while (1)
  {
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = parse(input);

    // std::cout << "Token number is: " << tokens.size() << "\n";
    // for (std::string token : tokens)
    // {
    //   std::cout << token << ' ';
    // }
    // std::cout << '\n';

    if (tokens.empty())
    {
      print_prompt();
      continue;
    }

    std::string command = tokens.front();
    tokens.erase(tokens.begin());

    commands.run_cmd(command, tokens);
    print_prompt();
  }
}
