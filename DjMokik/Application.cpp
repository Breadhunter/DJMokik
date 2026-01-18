#include "Application.h"
#include <iostream>

bool Application::init() {

    if (!window.init(800, 600, "DjMokik")) {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    if (!engine.init(window)) {
        std::cerr << "Failed to init engine!" << std::endl;
        return false;
    }

    return true;
}

void Application::run() {
    engine.run(window);
}

void Application::cleanup() {
    engine.cleanup();
    window.cleanup();
}
