#ifndef SHOOTINGRANGE_SCENE_H
#define SHOOTINGRANGE_SCENE_H

#include <vector>
#include "handlers/CubeHandler.h"

class Scene {

private:

    /**
     * The cubes that make up the scene
     */
    std::vector<Cube> cubes;

    /**
     * The cube handler
     */
    CubeHandler &cubeHandler = CubeHandler::getInstance();

public:

    /**
     * Constructor
     */
    Scene();

    /**
     * Draw the scene
     */
    void draw();
};

#endif //SHOOTINGRANGE_SCENE_H
