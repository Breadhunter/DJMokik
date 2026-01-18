#pragma once

#include "VulkanRenderContext.h"
#include "VulkanRenderer.h"
#include "Scene.h"
#include "Window.h"


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
};
