#ifndef SHOOTINGRANGE_CUBE_H
#define SHOOTINGRANGE_CUBE_H

#include "handlers/ShaderHandler.h"

class Cube {

private:

    /**
     * The shader manager
     */
    ShaderHandler &shaderManager = ShaderHandler::getInstance();

    /**
     * The vertex array object
     */
    unsigned int VAO = 0;

    /**
     * The vertex buffers objects
     */
    unsigned int VBO = 0;

    /**
     * The brick texture
     */
    unsigned int texture = 0;

public:

    /**
     * Constructor
     */
    Cube() = default;

    /**
     * Initialize the cube
     * @param shader The reference to the vertex shader
     */
    void load();

    /**
     * Draw a cube
     *
     * @param position The position of the cube
     */
    void draw(glm::vec3 position) const;
};

#endif //SHOOTINGRANGE_CUBE_H
