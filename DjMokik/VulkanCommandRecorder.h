#pragma once
#include "VulkanCommand.h"
#include "VulkanSwapchain.h"
#include "VulkanPipeline.h"
#include "VulkanMesh.h"
#include "RenderObject.h"

class VulkanCommandRecorder {
public:
    void init(VulkanCommand& command);

    bool record(
        VulkanSwapchain& swapchain,
        VulkanPipeline& pipeline,
        VulkanMesh& mesh
    );

    bool recordScene(
        VulkanSwapchain&,
        VulkanPipeline&,
        const std::vector<RenderObject>&
    );



private:
    VulkanCommand* command = nullptr;
};
