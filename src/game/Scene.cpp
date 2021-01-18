#include "game/Scene.h"

Scene::Scene() {
    // Setup the room
    CubeGroup floorGroup, wallGroup;
    for (int m = -ROOM_SIZE; m <= ROOM_SIZE; m++) {
        for (int n = -ROOM_SIZE; n <= ROOM_SIZE; n++) {
            if (abs(m) == ROOM_SIZE || (abs(n) == ROOM_SIZE)) {
                for (int y = 1; y < ROOM_HEIGHT && (y < 2 || n < ROOM_SIZE - 1); y++) {
                    Cube wall{cubeHandler.brick};
                    wall.position = glm::vec3{(float) m, y, (float) n};
                    wall.update();
                    wallGroup.cubes.push_back(wall);
                }
            } else {
                Cube floor{cubeHandler.brick};
                floor.position = glm::vec3{(float) m, 0, (float) n};
                floor.update();
                floorGroup.cubes.push_back(floor);
            }
        }
    }
    room.groups.push_back(floorGroup);
    room.groups.push_back(wallGroup);
    floorGroup.position = glm::vec3{0, ROOM_HEIGHT, 0};
    floorGroup.update();
    room.groups.push_back(floorGroup);

    // Create the logo
    int bricks[7][5]{
            {0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1}
    };
    CubeGroup logoGroup;
    float scale = 0.1;
    for (int m = 0; m < 7; m++) {
        for (int n = 0; n < 5; n++) {
            if (bricks[m][n] > 0) {
                Cube cube{cubeHandler.empty};
                cube.position = glm::vec3{scale * (float) (n - 3), scale * (float) (5 - m), 0};
                cube.scale = glm::vec3{scale, scale, scale};
                cube.update();
                logoGroup.cubes.push_back(cube);
            }
        }
    }

    // Add the logo 4 times with different rotations
    logoGroup.pitch = 0.8f;
    logoGroup.position = glm::vec3{0, 0, 0.5};
    logoGroup.update();
    logo.groups.push_back(logoGroup);
    logoGroup.yaw = glm::pi<float>();
    logoGroup.position = glm::vec3{0, 0, -0.5};
    logoGroup.update();
    logo.groups.push_back(logoGroup);
    logoGroup.yaw = glm::pi<float>() / 2.0f;
    logoGroup.position = glm::vec3{0.5, 0, 0};
    logoGroup.update();
    logo.groups.push_back(logoGroup);
    logoGroup.yaw = 3 * glm::pi<float>() / 2.0f;
    logoGroup.position = glm::vec3{-0.5, 0, 0};
    logoGroup.update();
    logo.groups.push_back(logoGroup);
    logo.position = glm::vec3{0, 3, 0};
    logo.update();
}

void Scene::checkIntersections(ShotEvent shotEvent) {
    for (auto &target : targets) {
        // Calculate the angle
        glm::vec3 direct = target.position - shotEvent.start;
        double scalar = glm::dot(shotEvent.direction, direct);
        double alpha = acos((scalar) / (glm::length(shotEvent.direction) * glm::length(direct)));
        if (alpha > glm::pi<float>() / 2.0f) continue;

        // Calculate the direct distance
        double distance = glm::distance(shotEvent.start, target.position);

        // Calculate the minimum distance
        double minDistance = distance * sin(alpha);
        if (target.scale.x / 1.4f > minDistance) std::cout << minDistance << std::endl;
    }
}

void Scene::draw() {
    // Draw the room
    cubeHandler.draw(room);

    // Draw the logo
    logo.yaw = (float) glfwGetTime();
    logo.update();
    cubeHandler.draw(logo);
}