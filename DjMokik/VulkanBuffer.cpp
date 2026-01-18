#include "VulkanBuffer.h"
#include "VulkanDevice.h"
#include <stdexcept>
#include <cstring>

bool VulkanBuffer::create(
    VulkanDevice& device,
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties
) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device.getDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        return false;
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device.getDevice(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(
        device,
        memRequirements.memoryTypeBits,
        properties
    );

    if (vkAllocateMemory(device.getDevice(), &allocInfo, nullptr, &memory) != VK_SUCCESS) {
        return false;
    }

    vkBindBufferMemory(device.getDevice(), buffer, memory, 0);

    return true;
}

void VulkanBuffer::uploadData(
    VulkanDevice& device,
    const void* data,
    VkDeviceSize size
) {
    void* mapped;
    vkMapMemory(device.getDevice(), memory, 0, size, 0, &mapped);
    memcpy(mapped, data, (size_t)size);
    vkUnmapMemory(device.getDevice(), memory);
}

void VulkanBuffer::cleanup(VkDevice device) {
    if (buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(device, buffer, nullptr);
    }

    if (memory != VK_NULL_HANDLE) {
        vkFreeMemory(device, memory, nullptr);
    }
}

uint32_t VulkanBuffer::findMemoryType(
    VulkanDevice& device,
    uint32_t typeFilter,
    VkMemoryPropertyFlags properties
) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(device.getPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if (typeFilter & (1 << i) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}
