#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanSwapchain {
public:
    bool init(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface);
    bool createFramebuffers(VkDevice device, VkRenderPass renderPass);

    void cleanup(VkDevice device);

    VkSwapchainKHR get() const { return swapchain; }

    VkFormat getFormat() const { return imageFormat; }
    VkFormat getDepthFormat() const { return depthFormat; }

    VkExtent2D getExtent() const { return extent; }

    VkFramebuffer getFramebuffer(uint32_t index) const {
        return framebuffers[index];
    }

    uint32_t getImageCount() const {
        return static_cast<uint32_t>(images.size());
    }

private:
    bool createDepthResources(VkPhysicalDevice physicalDevice, VkDevice device);
    VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);

    VkSwapchainKHR swapchain = VK_NULL_HANDLE;

    VkFormat imageFormat;
    VkFormat depthFormat;

    VkExtent2D extent;

    VkImage depthImage = VK_NULL_HANDLE;
    VkDeviceMemory depthMemory = VK_NULL_HANDLE;
    VkImageView depthImageView = VK_NULL_HANDLE;

    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;
    std::vector<VkFramebuffer> framebuffers;
};
