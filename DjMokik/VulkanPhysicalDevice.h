
#pragma once
#include <vulkan/vulkan.h>

class VulkanPhysicalDevice {
public:
    VulkanPhysicalDevice(VkInstance instance);
    VkPhysicalDevice get();

private:
    VkPhysicalDevice device{};
};
