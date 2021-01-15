#ifndef SHOOTINGRANGE_INTERPRETER_H
#define SHOOTINGRANGE_INTERPRETER_H

#include "Command.h"
#include <iostream>
#include <vector>

class Interpreter {

public:

    /**
     * The configuration handler
     */
    Configuration::Handler &configHandler = Configuration::Handler::getInstance();

    /**
     * Interpret a command
     */
    ConsoleLog interpret(char commandInput[]);

    /**
     * List all matching commands
     * @param commandInput The current input value
     * @return Return all the matching commands
     */
    static std::vector<std::string> getCandidates(char commandInput[]);
};

#endif //SHOOTINGRANGE_INTERPRETER_H
