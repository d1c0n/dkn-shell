#include "commands.hpp"

void Commands::run_cmd(std::string cmd_name, std::vector<std::string> cmd_args)
{
    if (commands.find(cmd_name) != commands.end())
    {
        if (cmd_name == "exit")
        {
            exit_fn(cmd_args);
        }
        else if (cmd_name == "echo")
        {
            echo_fn(cmd_args);
        }
        else if (cmd_name == "type")
        {
            type_fn(cmd_args);
        }
    }
    else
    {
        std::cout << cmd_name << ": command not found\n";
    }
}

void Commands::exit_fn(std::vector<std::string> cmd_args)
{
    for (std::string arg : cmd_args)
    {
        exit(std::stoi(arg));
    }
}

void Commands::echo_fn(std::vector<std::string> cmd_args)
{
    for (std::string arg : cmd_args)
    {
        std::cout << arg << " ";
    }
    std::cout << '\n';
}

void Commands::type_fn(std::vector<std::string> cmd_args)
{
    if (commands.find(cmd_args.at(0)) != commands.end())
    {
        std::cout << cmd_args.at(0) << " is a shell builtin";
    }
    else
    {
        std::cout << cmd_args.at(0) << ": not found";
    }
    std::cout << '\n';
}
