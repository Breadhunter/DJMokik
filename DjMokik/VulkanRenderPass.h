#pragma once
#include <vulkan/vulkan.h>

class VulkanDevice;

class VulkanRenderPass {
public:
    bool init(VulkanDevice& device, VkFormat imageFormat);
    void cleanup(VkDevice device);
    VkRenderPass get() const { return renderPass; }


private:
    VkRenderPass renderPass = VK_NULL_HANDLE;
};
