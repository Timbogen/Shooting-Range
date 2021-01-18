#include "game/Scene.h"

Scene::Scene() {
    int size = 6;
    for (int m = -size; m <= size; m++) {
        for (int n = -size; n <= size; n++) {
            Cube floor{cubeHandler.brick};
            floor.position = glm::vec3{(float) m, 0, (float) n};
            floor.update();
            cubes.push_back(floor);
            if (abs(m) == size || abs(n) == size) {
                Cube wall{cubeHandler.brick};
                wall.position = glm::vec3{(float) m, 1, (float) n};
                wall.update();
                cubes.push_back(wall);
            }
        }
    }
}

void Scene::draw() {
    for (auto &cube : cubes) {
        cubeHandler.draw(cube);
    }
}