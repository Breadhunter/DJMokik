#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanDevice;

class VulkanDescriptorPool {
public:
    bool init(VulkanDevice& device, uint32_t maxSets);
    void cleanup(VkDevice device);

    VkDescriptorPool get() const { return pool; }

    VkDescriptorSet allocateDescriptorSet(
        VkDevice device,
        VkDescriptorSetLayout layout
    );

    void updateDescriptorSet(
        VkDevice device,
        VkDescriptorSet descriptorSet,
        VkBuffer uniformBuffer,
        VkDeviceSize bufferSize
    );

private:
    VkDescriptorPool pool = VK_NULL_HANDLE;
};
