#ifndef SHOOTINGRANGE_CONSOLE_H
#define SHOOTINGRANGE_CONSOLE_H

#include "handlers/InputHandler.h"
#include "handlers/ConfigurationHandler.h"
#include "Interpreter.h"
#include <queue>

/**
 * True if the command input should not overwrite a new text value
 */
extern bool maintainValue;

/**
 * The input of the console
 */
extern char input[];

class Console {

private:

    /**
     * The selected tooltip completion
     */
    int selected = -1;

    /**
     * Command candidates that match the current command input
     */
    std::vector<std::string> candidates;

    /**
     * The console log
     */
    std::vector<ConsoleLog> consoleLog;

    /**
     * The recent fps numbers
     */
    std::deque<int> recentFPSCount;

    /**
     * The GLFW window
     */
    GLFWwindow *window = nullptr;

    /**
     * The input handler
     */
    InputHandler &inputHandler = InputHandler::getInstance();

    /**
     * The input handler
     */
    Configuration::Handler &configHandler = Configuration::Handler::getInstance();

    /**
     * The interpreter
     */
    Interpreter interpreter;

public:

    /**
     * Initialize the console
     * @param window The open GLFW window
     */
    void initialize(GLFWwindow *window);

    /**
     * Draw the UI
     */
    void draw();

private:

    /**
     * Draw the console
     */
    void drawConsole();

};

#endif //SHOOTINGRANGE_CONSOLE_H
