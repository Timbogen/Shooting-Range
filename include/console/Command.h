#ifndef SHOOTINGRANGE_COMMAND_H
#define SHOOTINGRANGE_COMMAND_H

#include <iostream>
#include <utility>
#include <vector>
#include "handlers/ConfigurationHandler.h"

struct ConsoleLog {
    /**
     * True if the log is an error message
     */
    bool error;
    /**
     * The message
     */
    std::vector<std::string> message;
};

struct Command {
    /**
     * The commands
     */
    const static Command SET_FOV, GET_FOV, SET_MOUSE_SPEED, GET_MOUSE_SPEED, SET_WIRE_MODE, FPS_DISPLAY, SET_FPS_LIMIT,
            HELP;

    /**
     * The list of commands
     */
    static std::vector<Command> commands;

    /**
     * Name of the command
     */
    std::string name;

    /**
     * The execute function
     */
    std::function<ConsoleLog(std::vector<std::string> &, Configuration::Handler &)> execute;

    /**
     * Constructor
     * @param name The name of the command
     * @param execute The execute function
     */
    Command(std::string name,
            std::function<ConsoleLog(std::vector<std::string> &, Configuration::Handler &) noexcept(false)> execute) :
            name(std::move(name)), execute(std::move(execute)) {
        commands.push_back(*this);
    }

    /**
     * Constructor
     * @param name The name of the command
     */
    explicit Command(std::string name) : name(std::move(name)) {}
};

#endif //SHOOTINGRANGE_COMMAND_H
