#ifndef SHOOTINGRANGE_SHADERHANDLER_H
#define SHOOTINGRANGE_SHADERHANDLER_H

#include <glm/glm.hpp>

class ShaderHandler {

public:

    /**
     * The reference to the shader program
     */
    unsigned int shader;

    /**
     * The currently active texture
     */
    unsigned int currentTexture = 0;

public:

    /**
     * Provide access to the singleton instance
     * @return The singleton instance
     */
    static ShaderHandler &getInstance() {
        static ShaderHandler instance;
        return instance;
    }

private:

    /**
     * Hide the constructor
     */
    ShaderHandler() = default;

public:

    /**
     * Delete copy-constructor
     */
    ShaderHandler(ShaderHandler const&) = delete;

    /**
     * Delete copy-operator
     */
    void operator=(ShaderHandler const&) = delete;

    /**
     * Load the shaders
     */
    void initialize();

    /**
     * Set the matrices necessary for the camera config (view and projection)
     * @param view The view matrix
     * @param projection The projection matrix
     */
    void setCamera(glm::mat4 view, glm::mat4 projection) const;

    /**
     * Set an uniform value
     * @param model The model matrix
     */
    void setModel(glm::mat4 model) const;

    /**
     * Change the texture
     * @param texture The new texture
     */
    void setTexture(unsigned int texture);

    /**
     * Change the color
     * @param red The red value
     * @param green The green value
     * @param blue The blue value
     * @param alpha The alpha value (opacity)
     */
    void setColor(float red, float green, float blue, float alpha) const;
};

#endif //SHOOTINGRANGE_SHADERHANDLER_H