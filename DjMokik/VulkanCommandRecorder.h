#pragma once
#include "VulkanCommand.h"
#include "VulkanSwapchain.h"
#include "VulkanPipeline.h"
#include "VulkanMesh.h"
#include "RenderObject.h"

class VulkanCommandRecorder {
public:
    void init(VulkanCommand& command);
    void setRenderPass(VkRenderPass pass) {
        renderPass = pass;
    }

    bool recordScene(
        VkRenderPass renderPass,
        VulkanSwapchain& swapchain,
        VulkanPipeline& pipeline,
        const std::vector<RenderObject>& objects
    );



private:
    VulkanCommand* command = nullptr;
    VkRenderPass renderPass;

};
