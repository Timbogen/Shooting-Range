#ifndef SHOOTINGRANGE_INPUTHANDLER_H
#define SHOOTINGRANGE_INPUTHANDLER_H

#include <map>
#include <string>
#include <functional>
#include <GLFW/glfw3.h>

class InputHandler {

public:

    /**
     * The possible event types
     */
    unsigned static const ON_PRESSED = 0, WHILE_PRESSED = 1, ON_RELEASED = 2, ON_MOVE = 3;

private:

    /**
     * The possible states for a key
     */
    unsigned static const RELEASED = 0, PRESSED = 1;

    /**
     * A map containing all the registered mouse events
     */
    std::map<int, std::function<void(int, double, double)>> mouseCallbacks;

    /**
     * A map containing all the registered mouse states
     */
    std::map<int, int> mouseStates;

    /**
     * A map containing all the registered key events
     */
    std::map<int, std::function<void(int)>> keyCallbacks;

    /**
     * A map containing all the registered key states
     */
    std::map<int, int> keyStates;

public:

    /**
     * Provide access to the singleton instance
     * @return The singleton
     */
    static InputHandler &getInstance() {
        static InputHandler instance;
        return instance;
    }

private:

    /**
     * Hide the constructor
     */
    InputHandler() = default;


public:

    /**
     * Delete copy-constructor
     */
    InputHandler(InputHandler const&) = delete;

    /**
     * Delete copy-operator
     */
    void operator=(InputHandler const&) = delete;

    /**
     * Process the user input
     * @param window The active window
     */
    void processInput(GLFWwindow *window);

    /**
     * Add mouse event
     * @param key The code for the matching mouse button
     * @param callback The callback that should be triggered
     */
    void addMouseEvent(int const &button, std::function<void(int, double, double)> const &callback);

    /**
     * Remove mouse event
     * @param key The code for the matching mouse button
     */
    void removeMouseEvent(int const &button);

    /**
     * Add key event
     * @param key The code for the matching key
     * @param callback The callback that should be triggered
     */
    void addKeyEvent(int const &key, std::function<void(int)> const &callback);

    /**
     * Remove key event
     * @param key
     */
    void removeKeyEvent(int const &key);

};

#endif //SHOOTINGRANGE_INPUTHANDLER_H
