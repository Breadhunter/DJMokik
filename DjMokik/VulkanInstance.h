
#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class VulkanInstance {
public:
    VulkanInstance();
    ~VulkanInstance();

    VkInstance get();

private:
    VkInstance instance{};
};
