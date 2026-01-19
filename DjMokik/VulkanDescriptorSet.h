#pragma once
#include <vulkan/vulkan.h>

class VulkanDescriptorSet {
public:
    bool allocate(
        VkDevice device,
        VkDescriptorPool pool,
        VkDescriptorSetLayout layout
    );

    void update(
        VkDevice device,
        VkBuffer uniformBuffer
    );

    VkDescriptorSet get() const { return set; }

private:
    VkDescriptorSet set = VK_NULL_HANDLE;
};
