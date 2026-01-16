#include "VulkanSurface.h"
#include <iostream>

bool VulkanSurface::init(VkInstance instance, GLFWwindow* window) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan surface!" << std::endl;
        return false;
    }
    return true;
}

void VulkanSurface::cleanup(VkInstance instance) {
    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
        surface = VK_NULL_HANDLE;
    }
}
