#include "handlers/ShaderHandler.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

/**
 * Read in a file
 * @param path The path to the file
 * @return A string containing the content of the file
 */
std::string readFile(const char *path) {
    // Open the file
    std::ifstream file(path);
    if (!file.is_open()) return "";

    // Get the input and return it
    std::string result((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    file.close();
    return result;
}

/**
 * Load a shader
 * @param path The path to the shader file
 * @param shaderType The type of the shader
 * @return The ID of the shader
 */
unsigned int loadShader(const char *path, const int &shaderType) {
    // Load the shader
    std::string shaderFile = readFile(path);
    const char *shaderSource = shaderFile.c_str();
    unsigned int shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    // Check if it was successful
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cout << "WARNING! Loading shaders failed!" << std::endl << infoLog << std::endl;
    }
    return shaderID;
}

void ShaderHandler::load() {
    // Load the shaders and combine them into one shader program
    unsigned int vertexShader = loadShader("rsc/shaders/vertex.glsl", GL_VERTEX_SHADER);
    unsigned int fragmentShader = loadShader("rsc/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if the linking was successful
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "WARNING! Linking shaders failed!" << std::endl << infoLog << std::endl;
    }

    // Delete the single shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderHandler::setCamera(glm::mat4 view, glm::mat4 projection) const {
    unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
}

void ShaderHandler::setModel(glm::mat4 model) const {
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}