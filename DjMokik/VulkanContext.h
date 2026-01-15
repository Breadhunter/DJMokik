
#pragma once
#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanRenderer.h"

class VulkanContext {
public:
    VulkanContext(GLFWwindow* window);

    void draw();
    void waitIdle();

private:
    VulkanInstance instance;
    VulkanSurface surface;
    VulkanPhysicalDevice physical;
    VulkanDevice device;
    VulkanSwapchain swapchain;
    VulkanRenderer renderer;
};
