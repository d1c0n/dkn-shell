# DKN-shell

This is a C++ implementation of the ["Build Your Own Shell" Challenge](https://app.codecrafters.io/courses/shell/overview), a POSIX compliant shell that's capable of interpreting shell commands, running external programs and builtin commands like cd, pwd, echo and more.

# Building

1. Ensure you have `cmake` and `vcpkg` and a compatible compiler (`gcc` or `clan`) installed locally.
2. Run `g++ src/main.cpp src/commands.cpp src/parser.cpp`.

# Running

Run the compiled `a.out`.

or

Download the latest release and `chmod +x ./dknshell` to make executable, then run `./dknshell`.

or

Run the `run_program.sh` script to compile and run in one command.
