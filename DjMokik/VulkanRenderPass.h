#pragma once
#include <vulkan/vulkan.h>

class VulkanRenderPass {
public:
    bool init(VkDevice device);
    void cleanup(VkDevice device);

    VkRenderPass get() const;

private:
    VkRenderPass renderPass = VK_NULL_HANDLE;
};
