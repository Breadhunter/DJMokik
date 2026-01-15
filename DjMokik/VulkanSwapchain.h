#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanSwapchain {
public:
    VulkanSwapchain(VkPhysicalDevice physical, VkDevice device, VkSurfaceKHR surface);
    ~VulkanSwapchain();

    VkSwapchainKHR get() { return swap; }

    VkFormat getFormat() { return fmt; }

    VkExtent2D getExtent() { return ext; }

    std::vector<VkImageView>& getImageViews() { return imageViews; }

private:
    VkDevice device;
    VkSwapchainKHR swap;

    VkFormat fmt;
    VkExtent2D ext;

    std::vector<VkImageView> imageViews;
};
