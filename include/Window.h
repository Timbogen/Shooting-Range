#ifndef SHOOTINGRANGE_WINDOW_H
#define SHOOTINGRANGE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <console/Console.h>
#include "handlers/ConfigurationHandler.h"
#include "handlers/InputHandler.h"
#include "handlers/ShaderHandler.h"
#include "game/Scene.h"
#include "game/Player.h"

class Window {

private:

    /**
     * The title of the window
     */
    const char* title = "Shooting Range";

    /**
     * The active window
     */
    GLFWwindow *window = nullptr;

    /**
     * The key input manager
     */
    InputHandler &keyInputManager = InputHandler::getInstance();

    /**
     * The shader manager
     */
    ShaderHandler &shaderHandler = ShaderHandler::getInstance();

    /**
     * The shader manager
     */
    Configuration::Handler &configHandler = Configuration::Handler::getInstance();

    /**
     * The cubeHandler handler
     */
    CubeHandler &cubeHandler = CubeHandler::getInstance();

    /**
     * The console window
     */
    Console console;

    /**
     * The player
     */
    Player player;

    /**
     * The scene
     */
    Scene &scene = Scene::getInstance();

public:

    /**
     * Constructor
     */
    Window();

    /**
     * Initialize the window manager and start the update routine
     * @return False if the initialization failed
     */
    bool initialize();

private:

    /**
     * Start the game loop
     */
    void startGameLoop();

    /**
     * Update the display on refresh
     */
    void update();

    /**
     * Handle application exit
     */
    void onExit();
};

#endif //SHOOTINGRANGE_WINDOW_H
