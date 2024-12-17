#include <iostream>
#include <set>
int main()
{

  std::set<std::string> valid_commands{};

  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::cout << "$ ";

  std::string input;
  std::getline(std::cin, input);

  if (valid_commands.find(input) == valid_commands.end())
  {
    std::cout << input << ": command not found\n";
  }
}
