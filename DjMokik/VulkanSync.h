#pragma once
#include <vulkan/vulkan.h>

class VulkanSync {
public:
    bool init(VkDevice device);
    void cleanup(VkDevice device);

    VkSemaphore getImageAvailableSemaphore() const { return imageAvailableSemaphore; }
    VkFence getInFlightFence() const { return inFlightFence; }

private:
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;
};
