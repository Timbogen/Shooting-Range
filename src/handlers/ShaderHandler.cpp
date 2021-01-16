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

/**
 * Load a shader program
 * @param fragmentPath The path to the fragment shader
 * @return The program id
 */
unsigned int loadProgram(const char *fragmentPath) {
    // Load the shaders and combine them into one shader program
    unsigned int vertexShader = loadShader("rsc/shaders/vertex.glsl", GL_VERTEX_SHADER);
    unsigned int fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check if the linking was successful
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "WARNING! Linking shaders failed!" << std::endl << infoLog << std::endl;
    }

    // Delete the single shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

void ShaderHandler::initialize() {
    shader = loadProgram("rsc/shaders/fragment.glsl");
}

void ShaderHandler::setCamera(glm::mat4 view, glm::mat4 projection) const {
    glm::mat4 pv = projection * view;
    unsigned int pvLoc  = glGetUniformLocation(shader, "pv");
    glUniformMatrix4fv(pvLoc, 1, GL_FALSE, &pv[0][0]);
}

void ShaderHandler::setModel(glm::mat4 model) const {
    unsigned int modelLoc = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void ShaderHandler::setTexture(unsigned int texture) {
    if (currentTexture == texture) return;
    currentTexture = texture;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void ShaderHandler::setColor(float red, float green, float blue, float alpha) const {
    glUniform4f(glGetUniformLocation(shader, "cubeColor"), red, green, blue, alpha);
}
