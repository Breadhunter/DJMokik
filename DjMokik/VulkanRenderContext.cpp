#include "VulkanRenderContext.h"
#include <iostream>

bool VulkanRenderContext::init(Window& window) {

    if (!instance.init("DjMokik"))
        return false;

    if (!surface.init(instance.get(), window.get()))
        return false;

    if (!device.init(instance.get(), surface.get()))
        return false;

    if (!swapchain.init(
        device.getPhysicalDevice(),
        device.getDevice(),
        surface.get()
    ))
        return false;

    if (!renderPass.init(
        device.getDevice(),
        swapchain.getFormat(),
        swapchain.getDepthFormat()
    ))
        return false;

    if (!swapchain.createFramebuffers(
        device.getDevice(),
        renderPass.get()
    ))
        return false;

    if (!pipeline.init(device.getDevice(), renderPass.get()))
        return false;

    if (!command.init(
        device.getDevice(),
        swapchain,
        device.getGraphicsQueueFamily()
    ))
        return false;

    return true;
}

void VulkanRenderContext::cleanup() {

    vkDeviceWaitIdle(device.getDevice());

    sync.cleanup(device.getDevice());
    command.cleanup(device.getDevice());
    pipeline.cleanup(device.getDevice());
    swapchain.cleanup(device.getDevice());

    surface.cleanup(instance.get());
    device.cleanup();
    instance.cleanup();
}
