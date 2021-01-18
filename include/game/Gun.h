#ifndef SHOOTINGRANGE_GUN_H
#define SHOOTINGRANGE_GUN_H

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <deque>
#include <thread>
#include <mutex>
#include "handlers/ConfigurationHandler.h"
#include "handlers/CubeHandler.h"

struct Bullet {

    /**
     * Lifetime of a bullet
     */
    constexpr static double LIFETIME = 2.0;

    /**
     * Velocity of a bullet
     */
    constexpr static int VELOCITY = 100;

    /**
     * Color of a bullet
     */
    constexpr static glm::vec4 COLOR{0.85, 0.65, 0.13, 1.0};

    /**
     * Form of a bullet
     */
    constexpr static glm::vec3 SCALE{0.02, 0.02, 0.08};

    /**
     * Timestamp of cube start
     */
    double timestamp;

    /**
     * The direction vector of the cube
     */
    glm::vec3 direction;

    /**
     * The bullet cube itself
     */
    Cube cube;

    /**
     * Constructor
     * @param direction The direction vector of the cube
     * @param cube The bullet cube itself
     */
    Bullet(glm::vec3 &direction, Cube &cube) : direction(direction), cube(cube), timestamp(glfwGetTime()) {}
};

class Gun {

private:

    /**
     * The delay after shooting a cube
     */
    constexpr static double shootDelay = 0.1;

    /**
     * True if the gun should keep shooting
     */
    bool shooting = false;

    /**
     * The time of the last shot
     */
    double lastShot = 0.0;

    /**
     * The angles describing the looking direction of the player
     */
    float yaw = -90, pitch = 0;

    /**
     * The empty texture of the block
     * (stored in extra object so that there's no need for blocking resources
     * as this object will only be used from the shooting thread)
     */
    std::shared_ptr<unsigned int> texture;

    /**
     * The mutex object for multi-threading
     */
    std::mutex mutex;

    /**
     * The position of the player
     */
    glm::vec3 position{0.0f, 2.0f, -3.0f};

    /**
     * The shot bullets
     */
    std::deque<Bullet> bullets;

    /**
     * The actual gun model
     */
    CubeGroup gun;

    /**
     * The cube handler
     */
    CubeHandler &cubeHandler = CubeHandler::getInstance();

    /**
     * The config handler
     */
    Configuration::Handler &configHandler = Configuration::Handler::getInstance();

public:

    /**
     * Constructor
     */
    Gun();

    /**
     * Start shooting the gun
     */
    void startShooting();

    /**
     * Stop shooting the gun
     */
    void stopShooting();

    /**
     * Update and draw the gun
     * @param position The current position of the player
     * @param yaw The horizontal orientation of the player
     * @param pitch The vertical orientation of the player
     */
    void update(glm::vec3 &position, float yaw, float pitch);

private:

    /**
     * Continuously shoot the gun
     */
    void shoot();

};

#endif //SHOOTINGRANGE_GUN_H
