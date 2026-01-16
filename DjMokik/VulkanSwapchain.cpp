#include "VulkanSwapchain.h"
#include <iostream>

bool VulkanSwapchain::init(VkDevice device, VkSurfaceKHR surface) {
    // «десь можно добавить реальную настройку swapchain
    // ƒл€ компил€ции оставим просто заглушку
    swapchain = VK_NULL_HANDLE;
    std::cout << "Swapchain initialized (stub)" << std::endl;
    return true;
}

void VulkanSwapchain::cleanup(VkDevice device) {
    if (swapchain != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(device, swapchain, nullptr);
        swapchain = VK_NULL_HANDLE;
    }
}
