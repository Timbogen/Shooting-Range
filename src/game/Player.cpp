#include "Player.h"
#include <algorithm>

void Player::initialize(GLFWwindow *window) {
    // Add movement
    inputHandler.addKeyEvent(GLFW_KEY_W, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z += configHandler.config.deltaTime * SPEED_FORWARD * cos(yaw);
        position.x -= configHandler.config.deltaTime * SPEED_FORWARD * sin(yaw);
    });
    inputHandler.addKeyEvent(GLFW_KEY_S, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z -= configHandler.config.deltaTime * SPEED_FORWARD * cos(yaw);
        position.x += configHandler.config.deltaTime * SPEED_FORWARD * sin(yaw);
    });
    inputHandler.addKeyEvent(GLFW_KEY_A, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z += configHandler.config.deltaTime * SPEED_FORWARD * sin(yaw);
        position.x += configHandler.config.deltaTime * SPEED_FORWARD * cos(yaw);
    });
    inputHandler.addKeyEvent(GLFW_KEY_D, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z -= configHandler.config.deltaTime * SPEED_FORWARD * sin(yaw);
        position.x -= configHandler.config.deltaTime * SPEED_FORWARD * cos(yaw);
    });

    // Add mouse input
    glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    inputHandler.addMouseEvent(GLFW_MOUSE_BUTTON_LEFT, [this](int event, int posX, int posY) {
         updateCamera(posX - lastMouseX, posY - lastMouseY);
         lastMouseX = posX;
         lastMouseY = posY;
    });
}

void Player::updateCamera(double delta_x, double delta_y) {
    if (configHandler.config.consoleOpen) return;
    yaw += delta_x * MOUSE_SPEED_FACTOR * configHandler.config.mouseSensitivity;
    pitch -= delta_y * MOUSE_SPEED_FACTOR * configHandler.config.mouseSensitivity;
    pitch = std::min(std::max(pitch, -1.0), 1.0);
}

void Player::look() {
    // Calculate the direction vector
    glm::vec3 direction(
            cos(pitch) * sin(-yaw),
            sin(pitch),
            cos(pitch) * cos(-yaw)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(-yaw - 3.14f/2.0f),
            0,
            cos(-yaw - 3.14f/2.0f)
    );

    // Up vector
    glm::vec3 up = glm::cross( right, direction );
    glm::mat4 view = glm::lookAt(position, position + direction, up);

    // Set the projection matrix
    glm::mat4 projection = glm::perspective(
            glm::radians(configHandler.config.fov),
            (float) Configuration::width / (float) Configuration::height,
            0.1f,
            100.0f
    );
    shaderHandler.setCamera(view, projection);
}