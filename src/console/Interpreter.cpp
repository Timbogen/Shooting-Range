#include <algorithm>
#include "console/Interpreter.h"

/**
 * Split a string
 * @param commandInput The input string
 * @param split The split char
 */
std::vector<std::string> splitString(char commandInput[], char split) {
    std::vector<std::string> strings;
    std::string nextString;
    for (int i = 0; i < strlen(commandInput); i++) {
        if (commandInput[i] == split) {
            if (!nextString.empty()) {
                std::transform(nextString.begin(), nextString.end(), nextString.begin(), ::tolower);
                strings.push_back(nextString);
                nextString = "";
            }
        } else {
            nextString += commandInput[i];
        }
    }
    std::transform(nextString.begin(), nextString.end(), nextString.begin(), ::tolower);
    if (!nextString.empty()) strings.push_back(nextString);
    return strings;
}

ConsoleLog Interpreter::interpret(char commandInput[]) {
    // Check if the command is known and execute if it's the case
    std::vector<std::string> commands = splitString(commandInput, ' ');
    for (auto &command : Command::commands) {
        if (commands[0] == command.name) {
            return command.execute(commands, configHandler);
        }
    }

    // Refer to the help command
    return ConsoleLog{true, std::vector<std::string>{
            "Command not found!",
            std::string("Type in ").append(Command::HELP.name).append(" to get a list of commands.")
    }};
}

std::vector<std::string> Interpreter::getCandidates(char commandInput[]) {
    // Transform input to lower case
    std::string command{commandInput};
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    // Search for matching commands
    std::vector<std::string> result;
    if (command.empty()) return result;
    for (auto &candidate : Command::commands) {
        if (candidate.name.find(command) != std::string::npos && candidate.name != command) {
            result.push_back(candidate.name);
        }
    }
    return result;
}