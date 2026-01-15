#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanRenderer {
public:
    VulkanRenderer(
        VkDevice device,
        VkSwapchainKHR swapchain,
        std::vector<VkImageView>& imageViews,
        VkFormat format,
        VkExtent2D extent,
        VkQueue presentQueue
    );

    ~VulkanRenderer();

    void drawFrame();

private:
    VkDevice device;
    VkSwapchainKHR swapchain;
    std::vector<VkImageView> views;
    VkQueue queue;
};
