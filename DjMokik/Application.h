#pragma once
#include <string>
#include "Window.h"
#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanSwapchain.h"

class Application {
public:
    bool init();
    void run();
    void cleanup();

private:
    Window window;
    VulkanInstance instance;
    VulkanSurface surface;
    VulkanSwapchain swapchain;
};
