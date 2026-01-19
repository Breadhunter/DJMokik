#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanSwapchain.h"
#include "VulkanRenderPass.h"
#include "VulkanMesh.h"
#include "RenderObject.h"


class VulkanCommand {
public:
    bool init(VkDevice device, VulkanSwapchain& swapchain, uint32_t queueFamily);
    void cleanup(VkDevice device);

    const std::vector<VkCommandBuffer>& getBuffers() const { return commandBuffers; }

    VkCommandBuffer getCommandBuffer(uint32_t index) const {
        if (index < commandBuffers.size())
            return commandBuffers[index];

        return VK_NULL_HANDLE;
    };

    bool recordScene(
        VulkanSwapchain& swapchain,
        VkPipeline pipeline,
        VkPipelineLayout layout,
        const std::vector<RenderObject>& objects
    );




private:
    VkCommandPool commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers;
};
