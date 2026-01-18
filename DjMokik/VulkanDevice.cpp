#include "VulkanDevice.h"
#include <iostream>
#include <vector>

bool VulkanDevice::init(VkInstance instance, VkSurfaceKHR surface) {
    std::cout << "VulkanDevice::init called\n";

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        std::cout << "No Vulkan devices found\n";
        return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    physicalDevice = VK_NULL_HANDLE;

    for (auto dev : devices) {
        uint32_t queueCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueCount, nullptr);

        std::vector<VkQueueFamilyProperties> queues(queueCount);
        vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueCount, queues.data());

        for (uint32_t i = 0; i < queueCount; i++) {
            if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                physicalDevice = dev;
                graphicsQueueFamily = i;
                break;
            }
        }

        if (physicalDevice != VK_NULL_HANDLE)
            break;
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        std::cout << "Failed to find suitable GPU!\n";
        return false;
    }


    float priority = 1.0f;

    VkDeviceQueueCreateInfo queueInfo{};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = graphicsQueueFamily;
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &priority;

    const char* extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueInfo;
    createInfo.enabledExtensionCount = 1;
    createInfo.ppEnabledExtensionNames = extensions;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        std::cout << "Failed to create device\n";
        return false;
    }

    vkGetDeviceQueue(device, graphicsQueueFamily, 0, &graphicsQueue);
    vkGetDeviceQueue(device, graphicsQueueFamily, 0, &presentQueue);


    std::cout << "Vulkan device created\n";
    return true;
}


void VulkanDevice::cleanup() {
    if (device != VK_NULL_HANDLE) {
        vkDestroyDevice(device, nullptr);
        device = VK_NULL_HANDLE;
    }
    std::cout << "VulkanDevice::cleanup called\n";
}
