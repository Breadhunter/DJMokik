#include "VulkanDescriptorSetUtils.h"

namespace VulkanDescriptorSetUtils {

    VkDescriptorSet allocateDescriptorSet(
        VkDevice device,
        VkDescriptorPool pool,
        VkDescriptorSetLayout layout
    ) {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = pool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &layout;

        VkDescriptorSet descriptorSet;

        if (vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
            return VK_NULL_HANDLE;
        }

        return descriptorSet;
    }

    void updateDescriptorSet(
        VkDevice device,
        VkDescriptorSet descriptorSet,
        const VulkanUniformBuffer& ubo
    ) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = ubo.getBuffer();
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.dstSet = descriptorSet;
        write.dstBinding = 0;
        write.dstArrayElement = 0;
        write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        write.descriptorCount = 1;
        write.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(device, 1, &write, 0, nullptr);
    }

}
