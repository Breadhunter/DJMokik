#include "VulkanSwapchain.h"

bool VulkanSwapchain::init(
    VkPhysicalDevice physicalDevice,
    VkDevice device,
    VkSurfaceKHR surface
) {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formats.data());

    VkSurfaceFormatKHR surfaceFormat = formats[0];

    imageFormat = surfaceFormat.format;
    extent = capabilities.currentExtent;

    uint32_t imageCount = capabilities.minImageCount + 1;

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = imageFormat;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    createInfo.clipped = VK_TRUE;

    vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);

    vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
    images.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapchain, &imageCount, images.data());

    imageViews.resize(images.size());

    for (size_t i = 0; i < images.size(); i++) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = images[i];
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = imageFormat;

        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.layerCount = 1;

        vkCreateImageView(device, &viewInfo, nullptr, &imageViews[i]);
    }

    createDepthResources(physicalDevice, device);

    return true;
}

bool VulkanSwapchain::createFramebuffers(VkDevice device, VkRenderPass renderPass) {

    framebuffers.resize(images.size());

    for (size_t i = 0; i < images.size(); i++) {
        VkImageView attachments[] = {
            imageViews[i],
            depthImageView
        };

        VkFramebufferCreateInfo fbInfo{};
        fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fbInfo.renderPass = renderPass;
        fbInfo.attachmentCount = 2;
        fbInfo.pAttachments = attachments;
        fbInfo.width = extent.width;
        fbInfo.height = extent.height;
        fbInfo.layers = 1;

        vkCreateFramebuffer(device, &fbInfo, nullptr, &framebuffers[i]);
    }

    return true;
}

bool VulkanSwapchain::createDepthResources(VkPhysicalDevice physicalDevice, VkDevice device)
{
    depthFormat = findDepthFormat(physicalDevice);

    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = extent.width;
    imageInfo.extent.height = extent.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = depthFormat;
    imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

    vkCreateImage(device, &imageInfo, nullptr, &depthImage);

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, depthImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;

    VkPhysicalDeviceMemoryProperties memProps;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);

    for (uint32_t i = 0; i < memProps.memoryTypeCount; i++) {
        if (memRequirements.memoryTypeBits & (1 << i)) {
            allocInfo.memoryTypeIndex = i;
            break;
        }
    }

    vkAllocateMemory(device, &allocInfo, nullptr, &depthMemory);
    vkBindImageMemory(device, depthImage, depthMemory, 0);

    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = depthImage;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = depthFormat;

    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.layerCount = 1;

    vkCreateImageView(device, &viewInfo, nullptr, &depthImageView);

    return true;
}

VkFormat VulkanSwapchain::findDepthFormat(VkPhysicalDevice physicalDevice) {
    std::vector<VkFormat> candidates = {
        VK_FORMAT_D32_SFLOAT,
        VK_FORMAT_D24_UNORM_S8_UINT
    };

    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

        if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
            return format;
    }

    return VK_FORMAT_D32_SFLOAT;
}

void VulkanSwapchain::cleanup(VkDevice device) {
    vkDestroyImageView(device, depthImageView, nullptr);
    vkDestroyImage(device, depthImage, nullptr);
    vkFreeMemory(device, depthMemory, nullptr);

    for (auto fb : framebuffers)
        vkDestroyFramebuffer(device, fb, nullptr);

    for (auto view : imageViews)
        vkDestroyImageView(device, view, nullptr);

    vkDestroySwapchainKHR(device, swapchain, nullptr);
}
