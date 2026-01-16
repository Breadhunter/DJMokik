#pragma once
#include <vulkan/vulkan.h>

class VulkanSwapchain {
public:
    bool init(VkDevice device, VkSurfaceKHR surface);
    void cleanup(VkDevice device);

    VkSwapchainKHR get() const { return swapchain; } // <-- добавлено
    uint32_t getImageCount() const { return 2; }     // заглушка для компиляции

private:
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
};
