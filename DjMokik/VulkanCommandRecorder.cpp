#include "VulkanCommandRecorder.h"

void VulkanCommandRecorder::init(VulkanCommand& commandRef) {
    command = &commandRef;
}

bool VulkanCommandRecorder::record(
    VulkanSwapchain& swapchain,
    VulkanPipeline& pipeline,
    VulkanMesh& mesh
) {
    return command->recordCommands(
        swapchain,
        pipeline.get(),
        mesh.getVertexBuffer()
    );
}

bool VulkanCommandRecorder::recordScene(
    VulkanSwapchain& swapchain,
    VulkanPipeline& pipeline,
    const std::vector<RenderObject>& objects
) {
    return command->recordScene(
        swapchain,
        pipeline.get(),
        pipeline.getLayout(),
        objects
    );
}

