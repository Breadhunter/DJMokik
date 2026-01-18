#include "VulkanMesh.h"
#include "VulkanDevice.h"

bool VulkanMesh::create(VulkanDevice& device, const std::vector<Vertex>& vertices) {

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    if (!vertexBuffer.create(
        device,
        bufferSize,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    )) {
        return false;
    }

    vertexBuffer.uploadData(device, vertices.data(), bufferSize);

    return true;
}

void VulkanMesh::cleanup(VkDevice device) {
    vertexBuffer.cleanup(device);
}
