#include "console/Console.h"
#include <imgui.h>
#include <console/imgui/imgui_impl_glfw.h>
#include <console/imgui/imgui_impl_opengl3.h>

/**
 * True if the command input should not overwrite a new text value
 */
bool maintainValue;

/**
 * The input of the text field
 */
char input[1024] = {0};

void Console::initialize(GLFWwindow *glfwWindow) {
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    window = glfwWindow;
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    // Listen if the console should be opened
    inputHandler.addKeyEvent(GLFW_KEY_TAB, [this](int event) {
        if (event == InputHandler::ON_PRESSED) {
            configHandler.config.consoleOpen = !configHandler.config.consoleOpen;
            if (configHandler.config.consoleOpen) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            } else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    });

    // Check if a new command has to be processed
    inputHandler.addKeyEvent(GLFW_KEY_ENTER, [this](int event) {
        if (event == InputHandler::ON_PRESSED) {
            if (selected >= 0) {
                if (candidates.size() > selected) strcpy_s(input, candidates[selected].append(" ").c_str());
                selected = -1;
            } else if (strlen(input) != 0) {
                consoleLog.push_back(interpreter.interpret(input));
                memset(input, 0, IM_ARRAYSIZE(input));
            }
            maintainValue = true;
        }
    });

    // Check if the user tries to select a different tooltip completion
    inputHandler.addKeyEvent(GLFW_KEY_UP, [this](int event) {
        if (event == InputHandler::ON_PRESSED) {
            if (selected < (int) candidates.size() - 1) selected++;
            else selected = -1;
        }
    });
    inputHandler.addKeyEvent(GLFW_KEY_DOWN, [this](int event) {
        if (event == InputHandler::ON_PRESSED) {
            if (selected >= 0) selected--;
            else selected = (int) candidates.size() - 1;
        }
    });
}

void Console::draw() {
    // Show the UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (configHandler.config.showFPS) {
        // Get the current fps value
        recentFPSCount.push_back((int) (1.0f / configHandler.config.deltaTime));
        if (recentFPSCount.size() > 50) recentFPSCount.pop_front();
        float fps = 0;
        for (auto &value : recentFPSCount) fps += (float) value / recentFPSCount.size();

        // Draw the value
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::SetWindowSize(ImVec2(100, 40));
        ImGui::SetWindowPos(ImVec2(4.0f,4.0f));
        ImGui::Text("%s", std::to_string((int) fps).append(" FPS").c_str());
    }

    // Check if the console has to be drawn and draw crosshair otherwise
    if (!configHandler.config.consoleOpen) {
        ImGui::Begin("Crosshair", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::SetWindowSize(ImVec2(40, 40));
        ImGui::SetWindowPos(ImVec2(
                (float) Configuration::width / 2.0f - 20.0f,
                (float) Configuration::height / 2.0f - 20.0f
        ));
        ImGui::SetCursorPos(ImVec2(17, 13));
        ImGui::Text("+");
    } else {
        drawConsole();
    }

    // Render your GUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Console::drawConsole() {
    // Setup the window
    ImGui::Begin("Shooting Range Console", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    float width = (float) Configuration::width - 128;
    float height = (float) Configuration::height - 128;
    ImGui::SetWindowSize(ImVec2(width, height));
    ImGui::SetWindowPos(ImVec2(
            (float) Configuration::width / 2.0f - width / 2.0f,
            (float) Configuration::height / 2.0f - height / 2.0f
    ));

    // Draw the input field
    ImGui::SetCursorPos(ImVec2(20, height - 29.0f));
    ImGui::Text("Command:");
    ImGui::SetCursorPos(ImVec2(90, height - 32.0f));
    ImGui::SetKeyboardFocusHere();
    ImGui::PushItemWidth(width - 110);
    std::string inputCopy{input};
    ImGui::InputText(
            "",
            input,
            IM_ARRAYSIZE(input),
            ImGuiInputTextFlags_CallbackAlways,
            [](ImGuiInputTextCallbackData *data) {
                if (maintainValue) data->CursorPos = strlen(input);
                return 0;
            }
    );

    // Check if the value actually changed
    bool equalValue = inputCopy._Equal(input);
    if (maintainValue) {
        if (equalValue) maintainValue = false;
        strcpy_s(input, inputCopy.c_str());
    }
    if (!equalValue) {
        if (std::string{input}.empty()) selected = -1;
        candidates = Interpreter::getCandidates(input);
    }

    // Show the console log
    float offset = 48.0f;
    float textHeight = 20.0f;
    for (int i = (int) consoleLog.size() - 1; i >= 0; i--) {
        float logHeight = (float) consoleLog[i].message.size() * textHeight + 16.0f;

        // Draw the actual text
        ImVec4 color;
        if (consoleLog[i].error) color = ImVec4(1, 0, 0, 1);
        else color = ImVec4(1, 1, 1, 1);
        for (int j = 0; j < consoleLog[i].message.size(); j++) {
            ImGui::SetCursorPos(ImVec2(20, height - offset - textHeight * (float) (consoleLog[i].message.size() - j)));
            ImGui::TextColored(color, "%s", consoleLog[i].message[j].c_str());
        }

        // Draw the underline
        if (i != consoleLog.size() - 1) {
            float currentYPos = height - offset - 8.0f;
            ImGui::SetCursorPos(ImVec2(20, currentYPos));
            ImGui::Text("____________________");
            if (currentYPos < 0) return;
        }
        offset += logHeight;
    }

    // Show tooltip
    if (candidates.empty()) return;
    ImGui::SetNextWindowPos(ImVec2(150, height - candidates.size() * 17.0f + 15.0f));
    ImGui::SetNextWindowSize(ImVec2(200, candidates.size() * 17.0f + 12.0f));
    ImGui::BeginTooltip();
    for (int i = (int) candidates.size() - 1; i >= 0; i--) {
        if (i == selected) ImGui::TextColored(ImVec4(0.26, 0.38, 0.58, 1), "%s", candidates[i].c_str());
        else ImGui::Text("%s", candidates[i].c_str());
    }
    ImGui::EndTooltip();
}
