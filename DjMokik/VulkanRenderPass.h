#pragma once
#include <vulkan/vulkan.h>

class VulkanRenderPass {
public:
    bool init(VkDevice device, VkFormat color, VkFormat depth);
    void cleanup(VkDevice device);
    VkRenderPass get() const { return renderPass; }

private:
    VkRenderPass renderPass = VK_NULL_HANDLE;
};
