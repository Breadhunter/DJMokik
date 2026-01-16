#include "VulkanRenderer.h"
#include <vulkan/vulkan.h>

bool VulkanRenderer::init(VulkanDevice& device, VulkanSwapchain& swapchain, VulkanCommand& command, VulkanSync& sync) {
    this->device = &device;
    this->swapchain = &swapchain;
    this->command = &command;
    this->sync = &sync;
    return true;
}

void VulkanRenderer::drawFrame() {
    VkDevice vkDevice = device->getDevice();
    VkSemaphore sem = sync->getImageAvailableSemaphore();
    VkFence fence = sync->getInFlightFence();
    vkWaitForFences(vkDevice, 1, &fence, VK_TRUE, UINT64_MAX);
    vkResetFences(vkDevice, 1, &fence);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(vkDevice, swapchain->get(), UINT64_MAX, sem, VK_NULL_HANDLE, &imageIndex);
}

void VulkanRenderer::cleanup() {}
