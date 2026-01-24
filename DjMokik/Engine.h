#pragma once

#include "VulkanRenderContext.h"
#include "VulkanRenderer.h"
#include "Scene.h"
#include "Window.h"
#include <chrono>


class Engine {
public:
    bool init(Window& window);
    void run(Window& window);
    void cleanup();

    Scene& getScene();
    VulkanRenderer& getRenderer();

private:
    VulkanRenderContext context;
    VulkanRenderer renderer;
    Scene scene;

    float calculateDeltaTime();

    std::chrono::steady_clock::time_point lastTime;
};
