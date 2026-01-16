#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class VulkanSurface {
public:
    bool init(VkInstance instance, GLFWwindow* window);
    void cleanup(VkInstance instance);

    VkSurfaceKHR get() const { return surface; }

private:
    VkSurfaceKHR surface = VK_NULL_HANDLE;
};
