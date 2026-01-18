#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanSwapchain {
public:
    bool init(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface);
    void cleanup(VkDevice device);

    VkSwapchainKHR get() const { return swapchain; }

    uint32_t getImageCount() const { return static_cast<uint32_t>(images.size()); }

    VkFramebuffer getFramebuffer(uint32_t index) const { return framebuffers[index]; }
    VkExtent2D getExtent() const { return extent; }
    VkFormat getFormat() const { return imageFormat; }
    VkRenderPass getRenderPass() const { return renderPass; }


private:
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    VkFormat imageFormat;
    VkExtent2D extent;
    VkRenderPass renderPass = VK_NULL_HANDLE;

    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;
    std::vector<VkFramebuffer> framebuffers;
};
