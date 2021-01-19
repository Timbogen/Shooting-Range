#include "game/Player.h"
#include <chrono>

void Player::initialize(GLFWwindow *window) {
    // Add movement
    inputHandler.addKeyEvent(GLFW_KEY_W, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z += configHandler.config.deltaTime * SPEED_MOVING * cos(yaw);
        position.x -= configHandler.config.deltaTime * SPEED_MOVING * sin(yaw);
        checkBounds();
    });
    inputHandler.addKeyEvent(GLFW_KEY_S, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z -= configHandler.config.deltaTime * SPEED_MOVING * cos(yaw);
        position.x += configHandler.config.deltaTime * SPEED_MOVING * sin(yaw);
        checkBounds();
    });
    inputHandler.addKeyEvent(GLFW_KEY_A, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z += configHandler.config.deltaTime * SPEED_MOVING * sin(yaw);
        position.x += configHandler.config.deltaTime * SPEED_MOVING * cos(yaw);
        checkBounds();
    });
    inputHandler.addKeyEvent(GLFW_KEY_D, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        position.z -= configHandler.config.deltaTime * SPEED_MOVING * sin(yaw);
        position.x -= configHandler.config.deltaTime * SPEED_MOVING * cos(yaw);
        checkBounds();
    });
    inputHandler.addKeyEvent(GLFW_KEY_SPACE, [this](int event) {
        if (configHandler.config.consoleOpen) return;
        if (event == InputHandler::ON_PRESSED) inAir = true;
    });

    // Add mouse input
    glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    inputHandler.addMouseEvent(GLFW_MOUSE_BUTTON_LEFT, [this](int event, int posX, int posY) {
        // Update the camera
        updateCamera((float) (posX - lastMouseX), (float) (posY - lastMouseY));
        lastMouseX = posX;
        lastMouseY = posY;

        // Shoot the gun
        if (event == InputHandler::ON_PRESSED) gun.startShooting();
        else if (event == InputHandler::ON_RELEASED) gun.stopShooting();
    });
}

void Player::update() {
    // Calculate the view matrix
    glm::vec3 direction(cos(pitch) * sin(-yaw), sin(pitch), cos(pitch) * cos(-yaw));
    glm::vec3 right = glm::vec3(
            sin(-yaw - glm::pi<float>() / 2.0f),
            0,
            cos(-yaw - glm::pi<float>() / 2.0f)
    );
    glm::vec3 up = glm::cross(right, direction);
    glm::mat4 view = glm::lookAt(position, position + direction, up);

    // Calculate the projection matrix
    glm::mat4 projection = glm::perspective(
            glm::radians(configHandler.config.fov),
            (float) Configuration::width / (float) Configuration::height,
            0.1f,
            100.0f
    );
    shaderHandler.setCamera(view, projection);

    // Jump if necessary
    jump();

    // Update the gun and check if new shot event are available
    gun.update(position, yaw, pitch);
    if (gun.hasShotEvent()) scene.checkIntersections(gun.getShotEvent());
}

void Player::jump() {
    if (!inAir) return;
    jumpProgress += configHandler.config.deltaTime * SPEED_JUMPING;
    position.y = PLAYER_HEIGHT + sin(jumpProgress);
    if (jumpProgress > glm::pi<float>()) {
        inAir = false;
        jumpProgress = 0;
        position.y = PLAYER_HEIGHT;
    }
}

void Player::checkBounds() {
    float size = Scene::ROOM_SIZE - 1;
    position.x = std::max(position.x, -size);
    position.z = std::max(position.z, -size);
    position.x = std::min(position.x, size);
    position.z = std::min(position.z, size);
}

void Player::updateCamera(float delta_x, float delta_y) {
    if (configHandler.config.consoleOpen) return;
    yaw += delta_x * MOUSE_SPEED_FACTOR * configHandler.config.mouseSensitivity;
    pitch -= delta_y * MOUSE_SPEED_FACTOR * configHandler.config.mouseSensitivity;
    pitch = std::min(std::max(pitch, -1.5f), 1.5f);
}