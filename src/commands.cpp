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

bool Commands::is_internal(std::string cmd_name)
{
    return commands.find(cmd_name) != commands.end();
}

bool Commands::is_external(std::string cmd_name)
{
    return path_commands.find(cmd_name) != path_commands.end();
}

Commands::Commands()
{
    std::string path_env = std::getenv("PATH");

    std::stringstream ss(path_env);
    std::string path;
    while (!ss.eof())
    {
        getline(ss, path, ':');
        try
        {
            for (const auto &entry : std::filesystem::directory_iterator(path))
            {
                path_commands.insert({entry.path().filename().string(), entry.path()});
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
        }
    }
}

bool Commands::is_in_path(std::string cmd_name)
{

    std::string path_env = std::getenv("PATH");
    std::stringstream ss(path_env);
    std::string path;
    while (!ss.eof())
    {
        getline(ss, path, ':');
        std::string abs_path = path + '/' + cmd_name;
        if (std::filesystem::exists(abs_path))
        {
            return true;
        }
    }
    return false;
}

void Commands::run_external_executable(std::string cmd_name, std::vector<std::string> cmd_args)
{
    std::ostringstream command;
    command << cmd_name;
    for (const auto &arg : cmd_args)
    {
        command << " " << arg;
    }

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.str().c_str(), "r"), pclose);

    std::array<char, 128> buffer = {};
    std::string output;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        output += buffer.data();
    }

    std::cout << output;
}

void Commands::run_cmd(std::string cmd_name, std::vector<std::string> cmd_args)
{

    if (is_internal(cmd_name))
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
        else if (cmd_name == "pwd")
        {
            run_external_executable(cmd_name, cmd_args);
        }
    }
    else if (is_external(cmd_name) or is_in_path(cmd_name))
    {
        run_external_executable(cmd_name, cmd_args);
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
    if (is_internal(cmd_args.at(0)))
    {
        std::cout << cmd_args.at(0) << " is a shell builtin";
    }
    else if (is_external(cmd_args.at(0)))
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

void Commands::pwd_fn(std::vector<std::string> cmd_args)
{
    auto currentPath = std::filesystem::current_path();

    std::cout << currentPath << "\n";
}
