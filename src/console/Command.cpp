#include "console/Command.h"
#include <glad/glad.h>

/**
 * Define the commands list
 */
std::vector<Command> Command::commands = std::vector<Command>{};

/**
 * Command to set the fov
 */
const Command Command::SET_FOV = Command(
        "set_fov",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            try {
                if (args.size() > 1) {
                    float value = std::stof(args[1]);
                    if (value >= 40 && value <= 120) {
                        handler.config.fov = value;
                        handler.save();
                        return ConsoleLog{false, std::vector<std::string>{
                                std::string("Field of view was set to ").append(std::to_string(value)).append(".")
                        }};
                    }
                }
            } catch (std::exception const &e) {}
            return ConsoleLog{true, std::vector<std::string>{
                    "ERROR! Field of view has to be a numeric value between 40 and 120",
                    "Example: set_fov 70"
            }};
        }
);

/**
 * Command to get the fov
 */
const Command Command::GET_FOV = Command(
        "get_fov",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            return ConsoleLog{false, std::vector<std::string>{
                    std::string("Field of view is currently set to ")
                            .append(std::to_string(handler.config.fov))
                            .append(".")
            }};
        }
);

/**
 * Command to set the mouse sensitivity
 */
const Command Command::SET_MOUSE_SPEED = Command(
        "set_mouse_sensitivity",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            try {
                if (args.size() > 1) {
                    float value = std::stof(args[1]);
                    if (value >= 0.01f && value <= 100.0f) {
                        handler.config.mouseSensitivity = value;
                        handler.save();
                        return ConsoleLog{false, std::vector<std::string>{
                                std::string("Mouse sensitivity was set to ").append(std::to_string(value)).append(".")
                        }};
                    }
                }
            } catch (std::exception const &e) {}
            return ConsoleLog{true, std::vector<std::string>{
                    "ERROR! Mouse speed has to be a numeric value between 0.01 and 100",
                    "Example: set_mouse_sensitivity 2"
            }};
        }
);

/**
 * Command to get the mouse sensitivity
 */
const Command Command::GET_MOUSE_SPEED = Command(
        "get_mouse_sensitivity",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            return ConsoleLog{false, std::vector<std::string>{
                    std::string("Mouse sensitivity is currently set to ")
                            .append(std::to_string(handler.config.mouseSensitivity))
                            .append(".")
            }};
        }
);

/**
 * Command to set the wire mode
 */
const Command Command::SET_WIRE_MODE = Command(
        "set_wire_mode",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            try {
                if (args.size() > 1) {
                    if (args[1]._Equal("on")) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        return ConsoleLog{false, std::vector<std::string>{"Wire mode was turned on."}};
                    } else if (args[1]._Equal("off")) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        return ConsoleLog{false, std::vector<std::string>{"Wire mode was turned off."}};
                    }
                }
            } catch (std::exception const &e) {}
            return ConsoleLog{true, std::vector<std::string>{
                    "ERROR! The wire mode has two states: on or off",
                    "Example: set_wire_mode on"
            }};
        }
);

/**
 * Command to set the wire mode
 */
const Command Command::FPS_DISPLAY = Command(
        "fps_display",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            try {
                if (args.size() > 1) {
                    if (args[1]._Equal("on")) {
                        handler.config.showFPS = true;
                        handler.save();
                        return ConsoleLog{false, std::vector<std::string>{"FPS display was turned on."}};
                    } else if (args[1]._Equal("off")) {
                        handler.config.showFPS = false;
                        handler.save();
                        return ConsoleLog{false, std::vector<std::string>{"FPS display was turned off."}};
                    }
                }
            } catch (std::exception const &e) {}
            return ConsoleLog{true, std::vector<std::string>{
                    "ERROR! The fps display has two states: on or off",
                    "Example: display_fps on"
            }};
        }
);

/**
 * Command to set the mouse sensitivity
 */
const Command Command::SET_FPS_LIMIT = Command(
        "set_fps_limit",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            try {
                if (args.size() > 1) {
                    double value = std::stof(args[1]);
                    if (value >= 1.0f && value <= 1000.0f) {
                        // Set the fps and compensate the inaccuracy of the fps limit
                        handler.config.frameTime = 1.0 / (value + 0.0004 * value * value + 0.12 * value - 4.7);
                        handler.save();
                        return ConsoleLog{false, std::vector<std::string>{
                                std::string("FPS limit was set to ").append(std::to_string(value)).append(".")
                        }};
                    }
                }
            } catch (std::exception const &e) {}
            return ConsoleLog{true, std::vector<std::string>{
                    "ERROR! FPS limit has to be a numeric value between 1 and 1000",
                    "Example: set_fps_limit 144"
            }};
        }
);

/**
 * Command to show the list of commands
 */
const Command Command::HELP = Command(
        "help",
        [](std::vector<std::string> &args, Configuration::Handler &handler) -> ConsoleLog {
            return ConsoleLog{false, std::vector<std::string>{
                    "List of available commands:",
                    std::string("\t")
                            .append(Command::SET_FOV.name)
                            .append(" - Change the player's field of view"),
                    std::string("\t")
                            .append(Command::GET_FOV.name)
                            .append(" - Get the player's field of view"),
                    std::string("\t")
                            .append(Command::SET_MOUSE_SPEED.name)
                            .append(" - Change the player's mouse sensitivity"),
                    std::string("\t")
                            .append(Command::GET_MOUSE_SPEED.name)
                            .append(" - Get the player's mouse sensitivity"),
                    std::string("\t")
                            .append(Command::SET_WIRE_MODE.name)
                            .append(" - Render the scene in wire mode"),
                    std::string("\t")
                            .append(Command::FPS_DISPLAY.name)
                            .append(" - Show the fps count on the upper left corner"),
                    std::string("\t")
                            .append(Command::SET_FPS_LIMIT.name)
                            .append(" - Set the framerate limit")
            }};
        }
);
