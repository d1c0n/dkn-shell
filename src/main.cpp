#include <iostream>
#include <set>

void print_prompt()
{
  std::cout << "$ ";
}

int main()
{

  std::set<std::string> valid_commands{};

  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  print_prompt();

  while (1)
  {
    std::string input;
    std::getline(std::cin, input);

    if (input.size() == 0)
    {
    }

    else if (valid_commands.find(input) == valid_commands.end())
    {
      std::cout << input << ": command not found\n";
    }
    else
    {
    }
    print_prompt();
  }
}
