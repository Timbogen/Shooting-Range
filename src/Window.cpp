#include "Window.h"
#include <fstream>
#include <chrono>
#include <thread>

Window::Window() {
    configHandler.load();
}

bool Window::initialize() {
    // Initialize the OpenGL Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow((int) Configuration::width,(int) Configuration::height, title, nullptr, nullptr);

    // Check if the window was initialized successfully
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetWindowPos(window, (int) configHandler.config.x, (int) configHandler.config.y);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *glfwWindow, int newWidth, int newHeight) {
        Configuration::width = (float) newWidth;
        Configuration::height = (float) newHeight;
        glViewport(0, 0, newWidth, newHeight);
    });

    // Try to initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(0);

    // Load the shaders and start rendering
    console.initialize(window);
    player.initialize(window);
    shaderHandler.initialize();
    cubeHandler.initialize();
    startGameLoop();
    return true;
}

void Window::startGameLoop() {
    double lastStart = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        configHandler.config.deltaTime = (float) (glfwGetTime() - lastStart);
        lastStart = glfwGetTime();
        update();
        double end = glfwGetTime() - lastStart;
        int waitTime = (int) ((configHandler.config.frameTime - end) * 1e6);
        std::this_thread::sleep_for(std::chrono::microseconds(waitTime));
    }
    onExit();
}

void Window::onExit() {
    // Save window bounds
    int xPos, yPos;
    glfwGetWindowPos(window, &xPos, &yPos);
    configHandler.saveWindowBounds((float) xPos, (float) yPos);

    // De-allocate all resources
    glDeleteProgram(shaderHandler.shader);
    glfwTerminate();
}


void Window::update() {
    // Process input
    keyInputManager.processInput(window);

    // Render the scene
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderHandler.shader);
    player.update();
    scene.update();

    // Show the console
    console.draw();

    // Check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}