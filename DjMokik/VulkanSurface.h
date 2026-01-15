
#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class VulkanSurface {
public:
    VulkanSurface(VkInstance instance, GLFWwindow* window);
    ~VulkanSurface();

    VkSurfaceKHR get();

private:
    VkInstance instance;
    VkSurfaceKHR surface{};
};
