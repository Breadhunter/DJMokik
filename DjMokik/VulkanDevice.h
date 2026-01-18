#pragma once
#include <vulkan/vulkan.h>

class VulkanDevice {
public:
    VulkanDevice() = default;
    ~VulkanDevice() = default;

    bool init(VkInstance instance, VkSurfaceKHR surface);
    void cleanup();

    VkDevice getDevice() const { return device; }

    VkQueue getGraphicsQueue() const { return graphicsQueue; }
    VkQueue getPresentQueue() const { return presentQueue; }

    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }

    uint32_t getGraphicsQueueFamily() const { return graphicsQueueFamily; }



private:
    VkDevice device = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;

    uint32_t graphicsQueueFamily = 0;

};
