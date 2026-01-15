
#pragma once
#include <vulkan/vulkan.h>

class VulkanDevice {
public:
    VulkanDevice(VkPhysicalDevice physical);
    ~VulkanDevice();

    VkDevice get();
    VkQueue queue();

private:
    VkDevice device{};
    VkQueue graphicsQueue{};
};
