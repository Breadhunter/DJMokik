#pragma once
#include <vulkan/vulkan.h>
#include "UniformBufferObject.h"

class VulkanDevice;

class VulkanUniformBuffer {
public:
    bool init(VulkanDevice& device);
    void update(VulkanDevice& device, const UniformBufferObject& ubo);
    void cleanup(VkDevice device);

    VkBuffer getBuffer() const { return buffer; }

private:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
};
