#include "VulkanRenderPass.h"
#include <array>

bool VulkanRenderPass::init(VkDevice dev, VkFormat color, VkFormat depth) {

    VkAttachmentDescription colorAtt{};
    colorAtt.format = color;
    colorAtt.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAtt.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAtt.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAtt.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentDescription depthAtt{};
    depthAtt.format = depth;
    depthAtt.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAtt.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAtt.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorRef{ 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
    VkAttachmentReference depthRef{ 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

    VkSubpassDescription sub{};
    sub.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sub.colorAttachmentCount = 1;
    sub.pColorAttachments = &colorRef;
    sub.pDepthStencilAttachment = &depthRef;

    std::array<VkAttachmentDescription, 2> atts = { colorAtt, depthAtt };

    VkRenderPassCreateInfo ci{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
    ci.attachmentCount = 2;
    ci.pAttachments = atts.data();
    ci.subpassCount = 1;
    ci.pSubpasses = &sub;

    return vkCreateRenderPass(dev, &ci, nullptr, &renderPass) == VK_SUCCESS;
}

void VulkanRenderPass::cleanup(VkDevice dev) {
    vkDestroyRenderPass(dev, renderPass, nullptr);
}
