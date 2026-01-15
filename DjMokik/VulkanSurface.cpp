
#include "VulkanSurface.h"

VulkanSurface::VulkanSurface(VkInstance inst, GLFWwindow* window) {
    instance = inst;
    glfwCreateWindowSurface(instance, window, nullptr, &surface);
}

VulkanSurface::~VulkanSurface() {
    vkDestroySurfaceKHR(instance, surface, nullptr);
}

VkSurfaceKHR VulkanSurface::get() {
    return surface;
}
