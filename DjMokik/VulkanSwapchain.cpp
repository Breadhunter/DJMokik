
#include "VulkanSwapchain.h"

VulkanSwapchain::VulkanSwapchain(VkPhysicalDevice, VkDevice dev, VkSurfaceKHR surf) {
    device = dev;

    VkSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.surface = surf;
    info.minImageCount = 2;
    info.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
    info.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    info.imageExtent = {800, 600};
    info.imageArrayLayers = 1;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.presentMode = VK_PRESENT_MODE_FIFO_KHR;

    vkCreateSwapchainKHR(device, &info, nullptr, &swap);

    fmt = info.imageFormat;
    ext = info.imageExtent;

    uint32_t count;
    vkGetSwapchainImagesKHR(device, swap, &count, nullptr);

    std::vector<VkImage> images(count);
    vkGetSwapchainImagesKHR(device, swap, &count, images.data());

    imageViews.resize(count);

    for (uint32_t i = 0; i < count; i++) {
        VkImageViewCreateInfo v{};
        v.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        v.image = images[i];
        v.viewType = VK_IMAGE_VIEW_TYPE_2D;
        v.format = fmt;
        v.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        v.subresourceRange.levelCount = 1;
        v.subresourceRange.layerCount = 1;

        vkCreateImageView(device, &v, nullptr, &imageViews[i]);
    }
}

VulkanSwapchain::~VulkanSwapchain() {
    for (auto v : imageViews)
        vkDestroyImageView(device, v, nullptr);

    vkDestroySwapchainKHR(device, swap, nullptr);
}
