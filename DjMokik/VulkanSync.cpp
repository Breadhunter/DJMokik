#include "VulkanSync.h"
#include <iostream>

bool VulkanSync::init(VkDevice device) {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailable) != VK_SUCCESS ||
        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinished) != VK_SUCCESS ||
        vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {

        std::cerr << "Failed to create synchronization objects!" << std::endl;
        return false;
    }

    std::cout << "VulkanSync initialized\n";
    return true;
}

void VulkanSync::cleanup(VkDevice device) {
    if (imageAvailable != VK_NULL_HANDLE) {
        vkDestroySemaphore(device, imageAvailable, nullptr);
        imageAvailable = VK_NULL_HANDLE;
    }

    if (renderFinished != VK_NULL_HANDLE) {
        vkDestroySemaphore(device, renderFinished, nullptr);
        renderFinished = VK_NULL_HANDLE;
    }

    if (inFlightFence != VK_NULL_HANDLE) {
        vkDestroyFence(device, inFlightFence, nullptr);
        inFlightFence = VK_NULL_HANDLE;
    }

    std::cout << "VulkanSync cleaned up\n";
}
