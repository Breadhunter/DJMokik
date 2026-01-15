#include "VulkanContext.h"

VulkanContext::VulkanContext(GLFWwindow* window)
    : instance(),
    surface(instance.get(), window),
    physical(instance.get()),
    device(physical.get()),
    swapchain(physical.get(), device.get(), surface.get()),

    renderer(
        device.get(),
        swapchain.get(),
        swapchain.getImageViews(),
        swapchain.getFormat(),
        swapchain.getExtent(),
        device.queue()
    )
{
}

void VulkanContext::draw() {
    renderer.drawFrame();
}

void VulkanContext::waitIdle() {
    vkDeviceWaitIdle(device.get());
}
