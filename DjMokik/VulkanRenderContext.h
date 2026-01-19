#pragma once

#include "Window.h"

#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanCommand.h"
#include "VulkanSync.h"
#include "VulkanPipeline.h"

class VulkanRenderContext {
public:
    bool init(Window& window);
    void cleanup();

    VulkanDevice& getDevice() { return device; }
    VulkanSwapchain& getSwapchain() { return swapchain; }
    VulkanCommand& getCommand() { return command; }
    VulkanPipeline& getPipeline() { return pipeline; }
    VulkanRenderPass& getRenderPass() { return renderPass; }


private:
    VulkanInstance instance;
    VulkanSurface surface;
    VulkanDevice device;
    VulkanSwapchain swapchain;
    VulkanCommand command;
    VulkanSync sync;
    VulkanPipeline pipeline;
    VulkanRenderPass renderPass; 
};
