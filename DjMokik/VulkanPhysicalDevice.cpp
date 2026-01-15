
#include "VulkanPhysicalDevice.h"
#include <vector>

VulkanPhysicalDevice::VulkanPhysicalDevice(VkInstance instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);

    std::vector<VkPhysicalDevice> list(count);
    vkEnumeratePhysicalDevices(instance, &count, list.data());

    device = list[0];
}

VkPhysicalDevice VulkanPhysicalDevice::get() {
    return device;
}
