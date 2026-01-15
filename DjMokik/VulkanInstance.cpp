
#include "VulkanInstance.h"

VulkanInstance::VulkanInstance() {
    VkApplicationInfo app{};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    VkInstanceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &app;

    uint32_t count;
    const char** ext = glfwGetRequiredInstanceExtensions(&count);

    info.enabledExtensionCount = count;
    info.ppEnabledExtensionNames = ext;

    vkCreateInstance(&info, nullptr, &instance);
}

VulkanInstance::~VulkanInstance() {
    vkDestroyInstance(instance, nullptr);
}

VkInstance VulkanInstance::get() {
    return instance;
}
