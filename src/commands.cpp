#include "commands.hpp"

bool Commands::is_executable(std::filesystem::directory_entry const &entry)
{
    // Check if it is a regular file
    if (!entry.is_regular_file())
    {
        return false;
    }

    // Get the permissions of the file
    std::filesystem::perms permissions = entry.status().permissions();

    // Check execute permissions for owner, group, or others
    constexpr std::filesystem::perms execute_mask = std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec;

    return (permissions & execute_mask) != std::filesystem::perms::none;
}

Commands::Commands()
{
    std::string path = std::getenv("PATH");

    std::string directory{""};
    for (char c : path)
    {
        if (c == ':')
        {
            try
            {
                for (const auto &entry : std::filesystem::directory_iterator(directory))
                    if (is_executable(entry))
                    {
                        path_commands.insert({entry.path().filename(), entry.path()});
                    }
            }
            catch (const std::filesystem::filesystem_error &e)
            {
                continue;
            }
        }
        else
        {
            directory += c;
        }
    }
}

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
    else if (path_commands.find(cmd_args.at(0)) != path_commands.end())
    {
        std::string path = path_commands.at(cmd_args.at(0)).string();
        std::cout << cmd_args.at(0) << " is " << path;
    }
    else
    {
        std::cout << cmd_args.at(0) << ": not found";
    }
    std::cout << '\n';
}
