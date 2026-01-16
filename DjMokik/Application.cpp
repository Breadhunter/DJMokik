#include "Application.h"
#include <iostream>

bool Application::init() {
    // Инициализация окна
    if (!window.init(800, 600, "DjMokik")) {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    // Инициализация Vulkan Instance
    if (!instance.init("DjMokik")) {
        std::cerr << "Failed to init Vulkan Instance!" << std::endl;
        return false;
    }

    // Инициализация Vulkan Surface
    if (!surface.init(instance.get(), window.get())) {
        std::cerr << "Failed to create Vulkan Surface!" << std::endl;
        return false;
    }

    // Инициализация Swapchain
    if (!swapchain.init(instance.getDevice(), surface.get())) {
        std::cerr << "Failed to init Vulkan Swapchain!" << std::endl;
        return false;
    }

    return true;
}

void Application::run() {
    while (!window.shouldClose()) {
        window.pollEvents();
        // Тут позже будет рендеринг
    }
}

void Application::cleanup() {
    swapchain.cleanup(instance.getDevice());
    surface.cleanup(instance.get());
    instance.cleanup();
    window.cleanup();
}
