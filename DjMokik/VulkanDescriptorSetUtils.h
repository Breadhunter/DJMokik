#pragma once
#include <vulkan/vulkan.h>
#include "VulkanUniformBuffer.h"

namespace VulkanDescriptorSetUtils {

    VkDescriptorSet allocateDescriptorSet(
        VkDevice device,
        VkDescriptorPool pool,
        VkDescriptorSetLayout layout
    );

    void updateDescriptorSet(
        VkDevice device,
        VkDescriptorSet descriptorSet,
        const VulkanUniformBuffer& ubo
    );

}
