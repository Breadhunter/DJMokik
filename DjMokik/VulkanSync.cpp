#include "VulkanSync.h"
#include <iostream>

bool VulkanSync::init(VkDevice device) {
    VkSemaphoreCreateInfo semInfo{};
    semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    if (vkCreateSemaphore(device, &semInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS) return false;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    if (vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) return false;

    return true;
}

void VulkanSync::cleanup(VkDevice device) {
    if (imageAvailableSemaphore != VK_NULL_HANDLE) vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
    if (inFlightFence != VK_NULL_HANDLE) vkDestroyFence(device, inFlightFence, nullptr);
}
