#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanSwapchain.h"

class VulkanCommand {
public:
    bool init(VkDevice device, VulkanSwapchain& swapchain, uint32_t queueFamily);
    void cleanup(VkDevice device);

    const std::vector<VkCommandBuffer>& getBuffers() const { return commandBuffers; }

private:
    VkCommandPool commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers;
};
