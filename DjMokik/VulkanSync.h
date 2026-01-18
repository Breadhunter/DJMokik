#pragma once
#include <vulkan/vulkan.h>

class VulkanSync {
public:
    bool init(VkDevice device);
    void cleanup(VkDevice device);

    VkSemaphore getImageAvailable() const { return imageAvailable; }
    VkSemaphore getRenderFinished() const { return renderFinished; }
    VkFence getInFlightFence() const { return inFlightFence; }



private:
    VkSemaphore imageAvailable = VK_NULL_HANDLE;
    VkSemaphore renderFinished = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;
};
