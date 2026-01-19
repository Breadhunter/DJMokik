#include "VulkanDescriptorPool.h"
#include "VulkanDevice.h"
#include <stdexcept>

bool VulkanDescriptorPool::init(VulkanDevice& device, uint32_t maxSets)
{
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = maxSets;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = maxSets;

    if (vkCreateDescriptorPool(
        device.getDevice(),
        &poolInfo,
        nullptr,
        &pool
    ) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

void VulkanDescriptorPool::cleanup(VkDevice device)
{
    if (pool != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(device, pool, nullptr);
        pool = VK_NULL_HANDLE;
    }
}

VkDescriptorSet VulkanDescriptorPool::allocateDescriptorSet(
    VkDevice device,
    VkDescriptorSetLayout layout
)
{
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = pool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &layout;

    VkDescriptorSet descriptorSet;

    if (vkAllocateDescriptorSets(
        device,
        &allocInfo,
        &descriptorSet
    ) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate descriptor set!");
    }

    return descriptorSet;
}

void VulkanDescriptorPool::updateDescriptorSet(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkBuffer uniformBuffer,
    VkDeviceSize bufferSize
)
{
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffer;
    bufferInfo.offset = 0;
    bufferInfo.range = bufferSize;

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = descriptorSet;
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;

    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;

    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(
        device,
        1,
        &descriptorWrite,
        0,
        nullptr
    );
}
