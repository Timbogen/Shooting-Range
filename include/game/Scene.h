#ifndef SHOOTINGRANGE_SCENE_H
#define SHOOTINGRANGE_SCENE_H

#include <vector>
#include "handlers/CubeHandler.h"
#include "game/Gun.h"

class Scene {

public:

    /**
     * The distance from the center of the room to the wall
     */
    constexpr static int ROOM_SIZE = 5, ROOM_HEIGHT = 4;

private:

    /**
     * The cube handler
     */
    CubeHandler &cubeHandler = CubeHandler::getInstance();

    /**
     * The room group
     */
    CubeGroup room;

    /**
     * The logo group
     */
    CubeGroup logo;

    /**
     * The hittable targets
     */
    std::vector<Cube> targets;

public:

    /**
     * Provide access to the singleton instance
     * @return The singleton
     */
    static Scene &getInstance() {
        static Scene instance;
        return instance;
    }

private:

    /**
     * Hide the constructor
     */
    Scene();

public:

    /**
     * Delete copy-constructor
     */
    Scene(Scene const &) = delete;

    /**
     * Delete copy-operator
     */
    void operator=(Scene const &) = delete;

    /**
     * Check if a bullet intersects with something in the scene
     * @param shotEvent The recent shot event
     */
    void checkIntersections(ShotEvent shotEvent);

    /**
     * Draw the scene
     */
    void draw();
};

#endif //SHOOTINGRANGE_SCENE_H
