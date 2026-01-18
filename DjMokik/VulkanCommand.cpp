#include "VulkanCommand.h"
#include "RenderObject.h"

bool VulkanCommand::init(VkDevice device, VulkanSwapchain& swapchain, uint32_t queueFamily) {

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamily;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
        return false;

    uint32_t count = static_cast<uint32_t>(swapchain.getImageCount());
    commandBuffers.resize(count);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = count;

    if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
        return false;

    return true;
}

void VulkanCommand::cleanup(VkDevice device) {

    if (!commandBuffers.empty()) {
        vkFreeCommandBuffers(
            device,
            commandPool,
            static_cast<uint32_t>(commandBuffers.size()),
            commandBuffers.data()
        );
    }

    if (commandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(device, commandPool, nullptr);
        commandPool = VK_NULL_HANDLE;
    }
}

bool VulkanCommand::recordCommands(
    VulkanSwapchain& swapchain,
    VkPipeline pipeline,
    VkBuffer vertexBuffer
) {
    for (size_t i = 0; i < commandBuffers.size(); i++) {

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
            return false;

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapchain.getRenderPass();
        renderPassInfo.framebuffer = swapchain.getFramebuffer(i);
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapchain.getExtent();

        VkClearValue clearColor = { {{0.14f, 0.88f, 0.88f, 1.0f}} };

        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(
            commandBuffers[i],
            &renderPassInfo,
            VK_SUBPASS_CONTENTS_INLINE
        );

        if (pipeline != VK_NULL_HANDLE) {

            vkCmdBindPipeline(
                commandBuffers[i],
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                pipeline
            );

            VkBuffer buffers[] = { vertexBuffer };
            VkDeviceSize offsets[] = { 0 };

            vkCmdBindVertexBuffers(
                commandBuffers[i],
                0,
                1,
                buffers,
                offsets
            );

            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
        }

        vkCmdEndRenderPass(commandBuffers[i]);

        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
            return false;
    }

    return true;
}

bool VulkanCommand::recordScene(
    VulkanSwapchain& swapchain,
    VkPipeline pipeline,
    VkPipelineLayout layout,
    const std::vector<RenderObject>& objects
)
{
    for (size_t i = 0; i < commandBuffers.size(); i++) {

        VkCommandBuffer cmd = commandBuffers[i];

        vkResetCommandBuffer(cmd, 0);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkBeginCommandBuffer(cmd, &beginInfo);

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapchain.getRenderPass();
        renderPassInfo.framebuffer = swapchain.getFramebuffer((uint32_t)i);
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapchain.getExtent();

        VkClearValue clearColor = { {0.1f, 0.1f, 0.1f, 1.0f} };

        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

        // ---- ВОТ ГЛАВНОЕ ИСПРАВЛЕНИЕ ----

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapchain.getExtent().width;
        viewport.height = (float)swapchain.getExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        vkCmdSetViewport(cmd, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapchain.getExtent();

        vkCmdSetScissor(cmd, 0, 1, &scissor);

        vkCmdDraw(cmd, 3, 1, 0, 0);

        // ----------------------------------

        for (auto& obj : objects) {

            VkBuffer buffers[] = { obj.mesh->getVertexBuffer() };
            VkDeviceSize offsets[] = { 0 };

            vkCmdBindVertexBuffers(cmd, 0, 1, buffers, offsets);

            vkCmdDraw(cmd, 3, 1, 0, 0);
        }

        vkCmdEndRenderPass(cmd);
        vkEndCommandBuffer(cmd);
    }

    return true;
}






