#pragma once
#include <vulkan/vulkan.h>
#include <vector>        // <---- ÂÎÒ ÝÒÎ ÎÁßÇÀÒÅËÜÍÎ

class VulkanDevice;
class VulkanSwapchain;

class VulkanFrameManager {
public:
    bool init(VulkanDevice& device, uint32_t maxFramesInFlight);
    void cleanup(VkDevice device);

    uint32_t beginFrame(VulkanDevice& device, VulkanSwapchain& swapchain);

    void submitFrame(
        VulkanDevice& device,
        VkQueue graphicsQueue,
        VkCommandBuffer cmd,
        VulkanSwapchain& swapchain,
        uint32_t imageIndex
    );

private:
    struct FrameSync {
        VkSemaphore imageAvailable;
        VkSemaphore renderFinished;
        VkFence inFlight;
    };

    std::vector<FrameSync> frames;

    uint32_t currentFrame = 0;
    uint32_t maxFrames = 0;
};
