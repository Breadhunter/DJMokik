#include "VulkanUniformBuffer.h"
#include "VulkanDevice.h"
#include "VulkanBuffer.h"

bool VulkanUniformBuffer::init(VulkanDevice& device) {

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    VulkanBuffer temp;

    if (!temp.create(
        device,
        bufferSize,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    )) {
        return false;
    }

    buffer = temp.get();
    memory = temp.getMemory();

    return true;
}

void VulkanUniformBuffer::update(
    VulkanDevice& device,
    const UniformBufferObject& ubo
) {
    void* data;
    vkMapMemory(device.getDevice(), memory, 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(device.getDevice(), memory);
}

void VulkanUniformBuffer::cleanup(VkDevice device) {
    if (buffer) {
        vkDestroyBuffer(device, buffer, nullptr);
    }

    if (memory) {
        vkFreeMemory(device, memory, nullptr);
    }
}
