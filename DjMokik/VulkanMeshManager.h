#pragma once
#include <vector>
#include <memory>
#include "VulkanMesh.h"

class VulkanDevice;

class VulkanMeshManager {
public:
    bool init(VulkanDevice& device);

    VulkanMesh& createMesh(
        VulkanDevice& device,
        const std::vector<Vertex>& vertices
    );

    void cleanup(VkDevice device);

private:
    std::vector<std::unique_ptr<VulkanMesh>> meshes;
};
