#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <array>
class Commands
{
private:
    std::set<std::string> commands{"echo", "type", "exit", "pwd"};
    std::map<std::string, std::filesystem::path> path_commands{};

    bool is_executable(const std::filesystem::directory_entry &entry);

    bool is_internal(std::string cmd_name);
    bool is_external(std::string cmd_name);

    bool is_in_path(std::string cmd_name);

    void exit_fn(std::vector<std::string> cmd_args);
    void echo_fn(std::vector<std::string> cmd_args);
    void type_fn(std::vector<std::string> cmd_args);
    void pwd_fn(std::vector<std::string> cmd_args);
    void cd_fn(std::vector<std::string> cmd_args);

    void run_external_executable(std::string cmd_name, std::vector<std::string> cmd_args);

public:
    Commands();

    std::set<std::string> get_valid_commands()
    {
        return commands;
    }
    void run_cmd(std::string cmd_name, std::vector<std::string> cmd_args);
};