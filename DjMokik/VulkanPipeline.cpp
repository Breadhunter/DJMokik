#include "VulkanPipeline.h"

bool VulkanPipeline::init(VkDevice device, VkRenderPass renderPass) {

    // Пока делаем заглушку, чтобы Vulkan не падал

    VkPipelineLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    VkPipelineLayout layout;

    if (vkCreatePipelineLayout(device, &layoutInfo, nullptr, &layout) != VK_SUCCESS) {
        return false;
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

    pipelineInfo.stageCount = 0;
    pipelineInfo.pStages = nullptr;

    pipelineInfo.pVertexInputState = nullptr;
    pipelineInfo.pInputAssemblyState = nullptr;
    pipelineInfo.pViewportState = nullptr;
    pipelineInfo.pRasterizationState = nullptr;
    pipelineInfo.pMultisampleState = nullptr;
    pipelineInfo.pDepthStencilState = nullptr;
    pipelineInfo.pColorBlendState = nullptr;
    pipelineInfo.pDynamicState = nullptr;

    pipelineInfo.layout = layout;
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;

    VkResult result = vkCreateGraphicsPipelines(
        device,
        VK_NULL_HANDLE,
        1,
        &pipelineInfo,
        nullptr,
        &pipeline
    );

    vkDestroyPipelineLayout(device, layout, nullptr);

    if (result != VK_SUCCESS) {
        return false;
    }

    return true;
}

void VulkanPipeline::cleanup(VkDevice device) {
    if (pipeline != VK_NULL_HANDLE) {
        vkDestroyPipeline(device, pipeline, nullptr);
    }
}
