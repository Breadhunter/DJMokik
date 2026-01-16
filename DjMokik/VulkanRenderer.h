#pragma once
#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanCommand.h"
#include "VulkanSync.h"

class VulkanRenderer {
public:
    bool init(VulkanDevice& device, VulkanSwapchain& swapchain, VulkanCommand& command, VulkanSync& sync);
    void drawFrame();
    void cleanup();

private:
    VulkanDevice* device = nullptr;
    VulkanSwapchain* swapchain = nullptr;
    VulkanCommand* command = nullptr;
    VulkanSync* sync = nullptr;
};
