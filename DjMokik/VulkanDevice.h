#pragma once
#include <vulkan/vulkan.h>

class VulkanDevice {
public:
    VulkanDevice() = default;
    ~VulkanDevice() = default;

    // ќбъ€влени€ функций Ч только подписи
    bool init(VkInstance instance, VkSurfaceKHR surface);
    void cleanup();

    VkDevice getDevice() const { return device; }

private:
    VkDevice device = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};
