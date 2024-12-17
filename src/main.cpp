#include <iostream>
#include <map>
#include <vector>
#include <sstream>

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

void exit_fn(std::vector<std::string> const args)
{
  for (std::string arg : args)
  {
    exit(std::stoi(arg));
  }
}

int main()
{

  std::map<std::string, void (*)(std::vector<std::string>)> valid_commands;

  valid_commands["exit"] = &exit_fn;

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

    if (valid_commands.find(command) == valid_commands.end())
    {
      std::cout << input << ": command not found\n";
    }
    else
    {
      valid_commands.at(command)(tokens);
    }
    print_prompt();
  }
}
