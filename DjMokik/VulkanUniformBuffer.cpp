#include "VulkanUniformBuffer.h"
#include "VulkanDevice.h"
#include <cstring>

bool VulkanUniformBuffer::init(VulkanDevice& device) {
    // Здесь будет создание VkBuffer с флагом UNIFORM_BUFFER
    // (мы позже добавим полноценную реализацию через твой BufferUtils)

    return true;
}

void VulkanUniformBuffer::update(
    VulkanDevice& device,
    const UniformBufferObject& ubo
) {
    // маппинг памяти и копирование данных
}

void VulkanUniformBuffer::cleanup(VkDevice device) {
    vkDestroyBuffer(device, buffer, nullptr);
    vkFreeMemory(device, memory, nullptr);
}
