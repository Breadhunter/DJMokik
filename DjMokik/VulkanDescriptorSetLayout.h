#pragma once
#include <vulkan/vulkan.h>

class VulkanDescriptorSetLayout {
public:
    bool init(VkDevice device);
    void cleanup(VkDevice device);

    VkDescriptorSetLayout get() const { return layout; }

private:
    VkDescriptorSetLayout layout = VK_NULL_HANDLE;
};
