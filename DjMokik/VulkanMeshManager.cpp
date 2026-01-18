#include "VulkanMeshManager.h"

bool VulkanMeshManager::init(VulkanDevice& device) {
    return true;
}

VulkanMesh& VulkanMeshManager::createMesh(
    VulkanDevice& device,
    const std::vector<Vertex>& vertices
) {
    auto mesh = std::make_unique<VulkanMesh>();

    mesh->create(device, vertices);

    meshes.push_back(std::move(mesh));

    return *meshes.back();
}

void VulkanMeshManager::cleanup(VkDevice device) {
    for (auto& m : meshes) {
        m->cleanup(device);
    }

    meshes.clear();
}
