#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <set>

class Commands
{
private:
    std::set<std::string> commands{"echo", "type", "exit"};

    void exit_fn(std::vector<std::string> cmd_args);
    void echo_fn(std::vector<std::string> cmd_args);
    void type_fn(std::vector<std::string> cmd_args);

public:
    std::set<std::string> get_valid_commands()
    {
        return commands;
    }
    void run_cmd(std::string cmd_name, std::vector<std::string> cmd_args);
};