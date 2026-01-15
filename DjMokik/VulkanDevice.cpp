
#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VkPhysicalDevice physical) {
    float priority = 1.0f;

    VkDeviceQueueCreateInfo q{};
    q.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    q.queueFamilyIndex = 0;
    q.queueCount = 1;
    q.pQueuePriorities = &priority;

    const char* ext[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VkDeviceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.queueCreateInfoCount = 1;
    info.pQueueCreateInfos = &q;
    info.enabledExtensionCount = 1;
    info.ppEnabledExtensionNames = ext;

    vkCreateDevice(physical, &info, nullptr, &device);
    vkGetDeviceQueue(device, 0, 0, &graphicsQueue);
}

VulkanDevice::~VulkanDevice() {
    vkDestroyDevice(device, nullptr);
}

VkDevice VulkanDevice::get() { return device; }
VkQueue VulkanDevice::queue() { return graphicsQueue; }
