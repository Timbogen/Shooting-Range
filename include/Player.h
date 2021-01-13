#ifndef SHOOTINGRANGE_PLAYER_H
#define SHOOTINGRANGE_PLAYER_H

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "handlers/ShaderHandler.h"
#include "handlers/InputHandler.h"
#include "handlers/ConfigurationHandler.h"

class Player {

private:

    /**
     * The movement speed
     */
    constexpr const static double SPEED_FORWARD = 5, SPEED_SIDE = 3;

    /**
     * A factor to slow down the mouse speed
     */
    constexpr const static double MOUSE_SPEED_FACTOR = 0.001;

    /**
     * The position of the player
     */
    glm::vec3 position{0.0f, 2.0f, -3.0f};

    /**
     * The last mouse position
     */
    double lastMouseX = 0, lastMouseY = 0;

    /**
     * The angles describing the looking direction of the player
     */
    double yaw = -90, pitch = 0;

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
    void look();

private:

     /**
      * Update the looking direction of the player
      * @param delta_x The delta of the mouse movement on the x axis
      * @param delta_y The delta of the mouse movement on the y axis
      */
    void updateCamera(double delta_x, double delta_y);

};

#endif //SHOOTINGRANGE_PLAYER_H
