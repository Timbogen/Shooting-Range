#include "game/Gun.h"
#include <chrono>

Gun::Gun() {
    texture = cubeHandler.empty;

    // The front of the barrel
    Cube front = Cube{cubeHandler.empty};
    front.color = glm::vec4{0, 0, 0, 1};
    front.scale = glm::vec3{0.13, 0.13, 0.1};
    front.position = glm::vec3{-0.2, -0.2, 0.35};
    front.update();

    // The barrel
    Cube barrel{cubeHandler.empty};
    barrel.color = glm::vec4{0.2, 0.2, 0.2, 1};
    barrel.scale = glm::vec3{0.1, 0.1, 0.2};
    barrel.position = glm::vec3{-0.2, -0.2, 0.2};
    barrel.update();

    // The shaft
    Cube shaft{cubeHandler.empty};
    shaft.color = glm::vec4{0, 0, 0, 1};
    shaft.scale = glm::vec3{0.14, 0.14, 0.1};
    shaft.position = glm::vec3{-0.2, -0.2, 0.1};
    shaft.update();

    // Add the objects
    gun.cubes.push_back(front);
    gun.cubes.push_back(barrel);
    gun.cubes.push_back(shaft);

    // Add a rotated barrel
    barrel.roll = glm::pi<float>() / 4;
    barrel.scale = glm::vec3{0.09, 0.09, 0.2};
    barrel.update();
    gun.cubes.push_back(barrel);
}

void Gun::startShooting() {
    shooting = true;
    std::thread shootingThread(&Gun::shoot, this);
    shootingThread.detach();
}

void Gun::stopShooting() {
    shooting = false;
}

void Gun::update(glm::vec3 &newPosition, float newYaw, float newPitch) {
    position = newPosition;
    yaw = newYaw;
    pitch = newPitch;

    // Update the gun
    gun.yaw = -yaw + 0.1f;
    gun.pitch = -pitch - 0.1f;
    gun.position = position;
    gun.update();

    // Rotate the front of the barrel and draw the gun
    if (shooting) gun.cubes[0].roll += configHandler.config.deltaTime * 10.0f;
    else gun.cubes[0].roll = 0;
    gun.cubes[0].update();
    cubeHandler.draw(gun);

    // Draw the bullets
    mutex.lock();
    for (auto &bullet : bullets) {
        bullet.cube.position =
                bullet.cube.position + configHandler.config.deltaTime * Bullet::VELOCITY * bullet.direction;
        bullet.cube.update();
        cubeHandler.draw(bullet.cube);
    }
    if (!bullets.empty() && glfwGetTime() - bullets.front().timestamp > Bullet::LIFETIME) bullets.pop_front();
    mutex.unlock();
}

void Gun::shoot() {
    while (shooting) {
        // Make sure that the gun shoots in the right frequency
        double delay = shootDelay - (glfwGetTime() - lastShot);
        if (delay > 0) std::this_thread::sleep_for(std::chrono::microseconds((int) (delay * 1e6)));
        lastShot = glfwGetTime();

        // Check if the shooting already got cancelled
        if (!shooting) return;

        // Create the cube object
        glm::vec3 direction{sin(-yaw) * cos(pitch), sin(pitch), cos(-yaw) * cos(pitch)};
        Cube bullet{texture};
        bullet.position = position;
        bullet.color = Bullet::COLOR;
        bullet.scale = Bullet::SCALE;
        bullet.yaw = -yaw;
        bullet.pitch = -pitch;
        bullet.update();

        // Add it to the other bullets
        mutex.lock();
        bullets.emplace_back(direction, bullet);
        mutex.unlock();
    }
}