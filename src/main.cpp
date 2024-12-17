#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "commands.hpp"

void print_prompt()
{
  std::cout << "$ ";
}

std::vector<std::string> split(std::string const &text)
{
  std::vector<std::string> tokens{};
  std::string token{};

  std::istringstream sst{text};

  while (sst >> token)
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

    std::vector<std::string> tokens = split(input);

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
