#pragma once

#include "VulkanMesh.h"
#include "VulkanUniformBuffer.h"

class RenderObject {
public:
    VulkanMesh* mesh = nullptr;
    VulkanUniformBuffer ubo;
    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
};
