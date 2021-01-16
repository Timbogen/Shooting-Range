#include "game/Scene.h"

Scene::Scene() {
    for (int m = -10; m < 10; m++) {
        for (int n = -10; n < 10; n++) {
            Cube cube1{cubeHandler.brick};
            cube1.setPosition((float) m, 0, (float) n);
            cubes.push_back(cube1);
        }
    }
}

void Scene::draw() {
    for (auto &cube : cubes) {
        cubeHandler.draw(cube);
    }
}