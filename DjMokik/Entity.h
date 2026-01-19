#pragma once
#include "Transform.h"
#include "VulkanUniformBuffer.h"

class VulkanMesh;

struct Entity {
    VulkanMesh* mesh = nullptr;
    Transform transform;
};
