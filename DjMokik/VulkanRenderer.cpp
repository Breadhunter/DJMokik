#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer(
    VkDevice dev,
    VkSwapchainKHR sw,
    std::vector<VkImageView>& imageViews,
    VkFormat fmt,
    VkExtent2D ext,
    VkQueue q
) {
    device = dev;
    swapchain = sw;
    views = imageViews;
    queue = q;
}

VulkanRenderer::~VulkanRenderer() {
}

void VulkanRenderer::drawFrame() {
    // Заглушка
}
