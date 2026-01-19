#include "VulkanCommandRecorder.h"

void VulkanCommandRecorder::init(VulkanCommand& commandRef) {
    command = &commandRef;
}

bool VulkanCommandRecorder::recordScene(
    VkRenderPass renderPass,
    VulkanSwapchain& swapchain,
    VulkanPipeline& pipeline,
    const std::vector<RenderObject>& objects
){
    return command->recordScene(
        renderPass,
        swapchain,
        pipeline.get(),
        pipeline.getLayout(),
        objects
    );

}

