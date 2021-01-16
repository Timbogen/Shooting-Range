#ifndef SHOOTINGRANGE_CUBEHANDLER_H
#define SHOOTINGRANGE_CUBEHANDLER_H

#include "handlers/ShaderHandler.h"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Cube {

public:

    /**
     * The texture of the cube
     */
    std::shared_ptr<unsigned int> texture;
    /**
     * The color of the cube
     */
    float red, green, blue, alpha;
    /**
     * The model matrix
     */
    glm::mat4 model;

private:

    /**
     * The important view vector's
     */
    glm::vec3 position, rotation, scale;
    /**
     * The rotation angle
     */
    float rotationAngle;

public:

    /**
     * Constructor
     *
     * @param texture The texture of the cube
     */
    Cube(std::shared_ptr<unsigned int> texture);

    /**
     * Set the color of the cube
     * @param red The red value
     * @param green The green value
     * @param blue The blue value
     * @param alpha The alpha value (opacity)
     */
    void setColor(float red, float green, float blue, float alpha);

    /**
     * Set the position of the cube
     * @param position The new position vector
     */
    void setPosition(float x, float y, float z);

    /**
     * Set the rotation of the cube
     * @param rotationAngle The rotation angle (in degrees)
     * @param rotation The rotation vector
     */
    void setRotation(float x, float y, float z, float rotationAngle);

    /**
     * The scale vector
     * @param x The x value
     * @param y The y value
     * @param z The z value
     */
    void setScale(float x, float y, float z);

private:

    /**
     * Update the cubes model matrix
     */
    void update();
};

namespace CubeTexture {
}

class CubeHandler {

public:

    /**
     * The different textures
     */
    std::shared_ptr<unsigned int> brick = std::make_shared<unsigned int>(0),
            empty = std::make_shared<unsigned int>(0);

private:

    /**
     * The vertex array object
     */
    unsigned int VAO;

    /**
     * The vertex buffers objects
     */
    unsigned int VBO;

    /**
     * The shader manager
     */
    ShaderHandler &shaderManager = ShaderHandler::getInstance();

public:

    /**
     * Provide access to the singleton instance
     * @return The singleton
     */
    static CubeHandler &getInstance() {
        static CubeHandler instance;
        return instance;
    }

private:

    /**
     * Hide the constructor
     */
    CubeHandler() = default;


public:

    /**
     * Delete copy-constructor
     */
    CubeHandler(CubeHandler const&) = delete;

    /**
     * Delete copy-operator
     */
    void operator=(CubeHandler const&) = delete;

    /**
     * Initialize the cube
     * @param shader The reference to the vertex shader
     */
    void initialize();

    /**
     * Draw a cube
     *
     * @param cube The cube to be drawn
     */
    void draw(const Cube &cube) const;
};

#endif //SHOOTINGRANGE_CUBEHANDLER_H
