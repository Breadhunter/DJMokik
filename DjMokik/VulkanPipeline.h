#pragma once
#include <vulkan/vulkan.h>

class VulkanPipeline {
public:
    bool init(VkDevice device, VkRenderPass renderPass);
    void cleanup(VkDevice device);

private:
    VkPipeline pipeline = VK_NULL_HANDLE;
};
