#pragma once
#include "VulkanBuffer.h"
#include "Vertex.h"
#include <vector>

class VulkanDevice;

class VulkanMesh {
public:
    bool create(VulkanDevice& device, const std::vector<Vertex>& vertices);

    void cleanup(VkDevice device);

    VkBuffer getVertexBuffer() const {
        return vertexBuffer.get();
    }

private:
    VulkanBuffer vertexBuffer;
};
