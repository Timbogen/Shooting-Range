#ifndef SHOOTINGRANGE_PLAYER_H
#define SHOOTINGRANGE_PLAYER_H

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "handlers/ShaderHandler.h"
#include "handlers/InputHandler.h"
#include "handlers/ConfigurationHandler.h"
#include "Gun.h"

class Player {

private:

    /**
     * The movement speed
     */
    constexpr static float SPEED_MOVING = 5, SPEED_JUMPING = 5;

    /**
     * A factor to slow down the mouse speed
     */
    constexpr static float MOUSE_SPEED_FACTOR = 0.001;

    /**
     * The height of the player
     */
    constexpr static float PLAYER_HEIGHT = 2.0f;

    /**
     * The gun of the player
     */
    Gun gun;

    /**
     * The position of the player
     */
    glm::vec3 position{0.0f, PLAYER_HEIGHT, 0.0f};

    /**
     * The last mouse position
     */
    double lastMouseX = 0, lastMouseY = 0;

    /**
     * The angles describing the looking direction of the player
     */
    float yaw = 0, pitch = 0;

    /**
     * True if the player is currently jumping
     */
    bool inAir = false;

    /**
     * The jump progress
     */
    float jumpProgress = 0;

    /**
     * The shader handler
     */
    ShaderHandler& shaderHandler = ShaderHandler::getInstance();

    /**
     * The input handler
     */
    InputHandler& inputHandler = InputHandler::getInstance();

    /**
     * The configuration handler
     */
    Configuration::Handler &configHandler = Configuration::Handler::getInstance();

public:

    /**
     * Constructor
     */
    Player() = default;

    /**
     * Initialize the player
     */
    void initialize(GLFWwindow *window);

    /**
     * Move the player
     */
    void update();

private:

    /**
     * Make the player jump
     */
    void jump();

     /**
      * Update the looking direction of the player
      * @param delta_x The delta of the mouse movement on the x axis
      * @param delta_y The delta of the mouse movement on the y axis
      */
    void updateCamera(float delta_x, float delta_y);

};

#endif //SHOOTINGRANGE_PLAYER_H
