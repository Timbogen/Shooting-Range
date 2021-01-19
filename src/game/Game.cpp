#include <thread>
#include "game/Game.h"

bool Target::processHit() {
    health--;
    float relativeHealth = (float) health / (float) maxHealth;
    target.color = glm::vec4{1 - relativeHealth, relativeHealth, 0, 1};
    return health <= 0;
}

void Target::setRotation(float newSpeed, float newRadius) {
    speed = newSpeed;
    radius = newRadius;
}

Cube Target::getCube(float deltaTime) {
    rotation += speed * deltaTime;
    target.position = position;
    target.position.x += radius * std::cos(rotation);
    target.position.y += radius * std::sin(rotation);
    target.update();
    return target;
}

void Game::start() {
    if (starting || running) return;
    starting = true;
    score = 0;
    gameDuration = configHandler.config.gameDuration;
    maxTargets = configHandler.config.maxTargets;
    currentTargets = 0;
    targets = std::vector<Target>();
    std::thread gameThread(&Game::startGame, this);
    gameThread.detach();
}

void Game::stop() {
    starting = false;
    running = false;
    time = 0;
}

void Game::onHit(int index) {
    if (targets[index].processHit()) {
        targets.erase(targets.begin() + index);
        score++;
        currentTargets = targets.size();
    }
}

void Game::update() {
    // Check if a new target should be spawned
    if (newTarget) {
        // Set the position of the target
        Target target{configHandler.config.health, cubeHandler.empty};
        target.position = glm::vec3{
            distributionX(generator),
            distributionY(generator),
            distributionZ(generator)
        };

        // Set the rotation of the target
        int rotation = distributionX(generator);
        if (rotation % 4 != 0) target.setRotation(configHandler.config.targetSpeed, (float) rotation * 2.0f / MAX_X);

        // Add the target
        targets.push_back(target);
        currentTargets = targets.size();
        newTarget = false;
    }
    for (auto &target : targets) cubeHandler.draw(target.getCube(configHandler.config.deltaTime));
}

void Game::startGame() {
    // The starting countdown
    time = 3;
    while (time > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!starting || running) return;
        time--;
    }
    running = true;
    std::thread gameThread(&Game::gameLoop, this);
    gameThread.detach();
}

void Game::gameLoop() {
    // The main game loop
    time = 1 * gameDuration;
    while (time >= 0) {
        std::this_thread::sleep_for(std::chrono::seconds (1));
        if (!running) return;
        if (currentTargets < maxTargets) newTarget = true;
        time--;
    }
    running = false;
}