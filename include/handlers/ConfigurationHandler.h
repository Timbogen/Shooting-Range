#ifndef SHOOTINGRANGE_CONFIGURATIONHANDLER_H
#define SHOOTINGRANGE_CONFIGURATIONHANDLER_H

#include <fstream>
#include <iostream>
#include <cereal/archives/xml.hpp>

namespace Configuration {

    /**
     * The current window width
     */
    extern float width;

    /**
     * The current window height
     */
    extern float height;

    class Configuration {

    public:

        /**
         * The bounds of the window
         */
        float x = 200, y = 200, width = 1600, height = 800;

        /**
         * The minimum frame time (in seconds)
         */
        double frameTime = 0.006;

        /**
         * The mouse sensitivity
         */
        float mouseSensitivity = 0.5;

        /**
         * The field of view
         */
        float fov = 70.0f;

        /**
         * True if the fps count should be shown
         */
        bool showFPS = true;

        /**
         * The duration of one game
         */
        int gameDuration = 60;

        /**
         * The health of a target
         */
        int health = 6;

        /**
         * The max amount of targets that are alive at the same time
         */
        int maxTargets = 5;

        /**
         * The speed of the targets
         */
        float targetSpeed = 5;

        /**
         * The delta frame time (in seconds)
         */
        float deltaTime = frameTime;

        /**
         * True if the console is open
         */
        bool consoleOpen = false;

    public:

        /**
         * The serialization interface for cereal
         */
        template<class Archive>
        void serialize(Archive &ar) {
            ar(
                    cereal::make_nvp("x", x),
                    cereal::make_nvp("y", y),
                    cereal::make_nvp("width", width),
                    cereal::make_nvp("height", height),
                    cereal::make_nvp("frameTime", frameTime),
                    cereal::make_nvp("mouseSensitivity", mouseSensitivity),
                    cereal::make_nvp("fov", fov),
                    cereal::make_nvp("showFPS", showFPS),
                    cereal::make_nvp("gameDuration", gameDuration),
                    cereal::make_nvp("health", health),
                    cereal::make_nvp("maxTargets", maxTargets),
                    cereal::make_nvp("targetSpeed", targetSpeed)
            );
        }
    };

    class Handler {

    public:

        /**
         * The config file
         */
        const char *configFile = "configuration.xml";

        /**
         * The configuration
         */
        Configuration config;

    public:

        /**
         * Provide access to the singleton instance
         * @return The singleton
         */
        static Handler &getInstance() {
            static Handler instance;
            return instance;
        }

    private:

        /**
         * Hide the constructor
         */
        Handler() = default;

    public:

        /**
         * Delete copy-constructor
         */
        Handler(Handler const &) = delete;

        /**
         * Delete copy-operator
         */
        void operator=(Handler const &) = delete;

        /**
         * Save the configuration
         */
        void save() const;

        /**
         * Load the configuration
         */
        void load();

        /**
         * Save the window bounds
         * @param x The x position of the window
         * @param y The y position of the window
         */
        void saveWindowBounds(float x, float y);
    };
}

#endif //SHOOTINGRANGE_CONFIGURATIONHANDLER_H
