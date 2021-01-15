#include "handlers/ConfigurationHandler.h"
#include <fstream>

/**
 * Define the static window bounds variables
 */
float Configuration::width, Configuration::height;

void Configuration::Handler::save() const {
    try {
        std::ofstream os(configFile);
        {
            cereal::XMLOutputArchive archive_out(os);
            archive_out(CEREAL_NVP(config));
        }
    } catch (cereal::Exception &e) {
        std::cout << "WARNING! " << e.what() << std::endl;
    }
}

void Configuration::Handler::load() {
    // Load the config
    try {
        std::ifstream is(configFile);
        {
            cereal::XMLInputArchive archive_in(is);
            archive_in(config);
        }
    } catch (cereal::Exception &e) {
        save();
    }

    // Update the window bounds
    width = config.width;
    height = config.height;
}

void Configuration::Handler::saveWindowBounds(float x, float y) {
    config.x = x;
    config.y = y;
    config.width = width;
    config.height = height;
    save();
}