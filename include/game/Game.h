#ifndef SHOOTINGRANGE_GAME_H
#define SHOOTINGRANGE_GAME_H

#include "handlers/ConfigurationHandler.h"
#include "handlers/CubeHandler.h"
#include <random>

class Target {

public:

    /**
     * The cubeHandler target
     */
    Cube target{nullptr};

    /**
     * The position of the cube
     */
    glm::vec3 position{0, 0, 0};

private:

    /**
     * The current health
     */
    int health = 0;

    /**
     * The maximum health
     */
    int maxHealth = 0.0;

    /**
     * The current rotation
     */
    float rotation = 0.0;

    /**
     * The speed of the rotation
     */
    float speed = 0.0;

    /**
     * The radius of the motion
     */
    float radius = 1.0;

public:

    /**
     * Constructor
     */
    Target(int health, std::shared_ptr<unsigned int> texture) : health(health), maxHealth(health), target(texture) {
        target.color = glm::vec4{0, 1, 0, 1};
    }

    /**
     * Process a bullet hit
     * @return True if the target is dead
     */
    bool processHit();

    /**
     * Set the rotation of the cube
     * @param speed The rotation speed
     * @param radius The rotation radius
     */
    void setRotation(float speed, float radius);

    /**
     * @return An updated cube (respecting the current rotation)
     */
    Cube getCube(float deltaTime);
};

class Game {

private:

    /**
     * The spawn ranges
     */
    constexpr static int MIN_X = -30, MAX_X = 30, MIN_Y = 0, MAX_Y = 3, MIN_Z = 15, MAX_Z = 40;

public:

    /**
     * The current time
     */
    std::atomic<int> time{0};

    /**
     * The current score
     */
    std::atomic<int> score{0};

    /**
     * The game targets
     */
    std::vector<Target> targets;

private:

    /**
     * True if a new target can be spawned
     */
    std::atomic<bool> newTarget{false};

    /**
     * True if the game is currently running
     */
    std::atomic<bool> running{false};

    /**
     * The amount of current targets
     */
    std::atomic<int> currentTargets{0};

    /**
     * The game configurations
     */
    std::atomic<int> maxTargets{0}, gameDuration{0};

    /**
     * The random number generator
     */
    std::default_random_engine generator;

    /**
     * The random distributions
     */
    std::uniform_int_distribution<int>
            distributionX{MIN_X, MAX_X},
            distributionY{MIN_Y, MAX_Y},
            distributionZ{MIN_Z, MAX_Z};

    /**
     * The cubeHandler handler
     */
    CubeHandler &cubeHandler = CubeHandler::getInstance();

    /**
     * The configuration handler
     */
    Configuration::Handler &configHandler = Configuration::Handler::getInstance();

public:

    /**
     * Start the game
     */
    void start();

    /**
     * Stop the game
     */
    void stop();

    /**
     * Process a hit of a target
     * @param index The index of the target that was hit
     */
    void onHit(int index);

    /**
     * Draw the objects
     */
    void update();

private:

    /**
     * Start the game
     */
    void startGame();
};

#endif //SHOOTINGRANGE_GAME_H
