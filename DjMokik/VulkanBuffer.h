#pragma once
#include <vulkan/vulkan.h>

class VulkanDevice;

class VulkanBuffer {
public:
    VulkanBuffer() = default;

    bool create(
        VulkanDevice& device,
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties
    );

    void uploadData(VulkanDevice& device, const void* data, VkDeviceSize size);

    void cleanup(VkDevice device);

    VkBuffer get() const { return buffer; }
    VkDeviceMemory getMemory() const { return memory; }

private:
    uint32_t findMemoryType(
        VulkanDevice& device,
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties
    );

    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
};
