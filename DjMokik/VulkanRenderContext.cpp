#include "VulkanRenderContext.h"
#include <iostream>

bool VulkanRenderContext::init(Window& window) {

    if (!instance.init("DjMokik")) {
        std::cerr << "Failed to init Vulkan Instance!\n";
        return false;
    }

    if (!surface.init(instance.get(), window.get())) {
        std::cerr << "Failed to create Vulkan Surface!\n";
        return false;
    }

    if (!device.init(instance.get(), surface.get())) {
        std::cerr << "Failed to init Vulkan Device!\n";
        return false;
    }

    if (!swapchain.init(
        device.getPhysicalDevice(),
        device.getDevice(),
        surface.get()
    )) {
        std::cerr << "Failed to init Vulkan Swapchain!\n";
        return false;
    }

    if (!sync.init(device.getDevice())) {
        std::cerr << "Failed to init Vulkan Sync!\n";
        return false;
    }

    if (!command.init(
        device.getDevice(),
        swapchain,
        device.getGraphicsQueueFamily()
    )) {
        std::cerr << "Failed to init Vulkan Command!\n";
        return false;
    }

    if (!pipeline.init(device.getDevice(), swapchain.getRenderPass())) {
        std::cerr << "Failed to create pipeline\n";
        return false;
    }

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
