#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

class VulkanInstance {
public:
    bool init(const std::string& appName);
    void cleanup();

    VkInstance get() const { return instance; }
    VkDevice getDevice() const { return device; }  // <-- добавлено

private:
    VkInstance instance = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
};
