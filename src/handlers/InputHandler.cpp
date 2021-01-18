#include "handlers/InputHandler.h"

void InputHandler::processInput(GLFWwindow *window) {
    // Evaluate the events for the registered keys
    for (auto const& value : keyCallbacks) {
        if (glfwGetKey(window, value.first) == GLFW_PRESS) {
            // Check if the key was released before
            if (keyStates[value.first] == RELEASED) {
                value.second(ON_PRESSED);
            } else {
                value.second(WHILE_PRESSED);
            }
             keyStates[value.first] = PRESSED;
        } else {
            // Check if the key was pressed before
            if (keyStates[value.first] == PRESSED) {
                value.second(ON_RELEASED);
            }
            keyStates[value.first] = RELEASED;
        }
    }

    // Evaluate the events for the registered mouse buttons
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    for (auto const& value : mouseCallbacks) {
        if (glfwGetMouseButton(window, value.first) == GLFW_PRESS) {
            // Check if the key was released before
            if (mouseStates[value.first] == RELEASED) {
                value.second(ON_PRESSED, mouseX, mouseY);
            } else {
                value.second(WHILE_PRESSED, mouseX, mouseY);
            }
            mouseStates[value.first] = PRESSED;
        } else {
            // Check if the key was pressed before
            if (mouseStates[value.first] == PRESSED) {
                value.second(ON_RELEASED, mouseX, mouseY);
            } else {
                value.second(ON_MOVE, mouseX, mouseY);
            }
            mouseStates[value.first] = RELEASED;
        }
    }
}

void InputHandler::addMouseEvent(const int &button, const std::function<void(int, double, double)> &callback) {
    mouseCallbacks[button] = callback;
    mouseStates[button] = RELEASED;
}

void InputHandler::removeMouseEvent(const int &button) {
    mouseCallbacks.erase(button);
    mouseStates.erase(button);
}

void InputHandler::addKeyEvent(int const &key, std::function<void(int)> const &callback) {
    keyCallbacks[key] = callback;
    keyStates[key] = RELEASED;
}

void InputHandler::removeKeyEvent(const int &key) {
    keyCallbacks.erase(key);
    keyStates.erase(key);
}