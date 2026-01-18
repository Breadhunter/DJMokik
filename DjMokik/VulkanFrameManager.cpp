#include "VulkanFrameManager.h"
#include "VulkanDevice.h"
#include "VulkanSwapchain.h"

bool VulkanFrameManager::init(VulkanDevice& device, uint32_t maxFramesInFlight) {
    maxFrames = maxFramesInFlight;
    frames.resize(maxFrames);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint32_t i = 0; i < maxFrames; i++) {
        if (vkCreateSemaphore(device.getDevice(), &semaphoreInfo, nullptr, &frames[i].imageAvailable) != VK_SUCCESS ||
            vkCreateSemaphore(device.getDevice(), &semaphoreInfo, nullptr, &frames[i].renderFinished) != VK_SUCCESS ||
            vkCreateFence(device.getDevice(), &fenceInfo, nullptr, &frames[i].inFlight) != VK_SUCCESS) {
            return false;
        }
    }

    return true;
}

void VulkanFrameManager::cleanup(VkDevice device) {
    for (auto& f : frames) {
        vkDestroySemaphore(device, f.imageAvailable, nullptr);
        vkDestroySemaphore(device, f.renderFinished, nullptr);
        vkDestroyFence(device, f.inFlight, nullptr);
    }
}

uint32_t VulkanFrameManager::beginFrame(VulkanDevice& device, VulkanSwapchain& swapchain) {
    auto& frame = frames[currentFrame];

    vkWaitForFences(device.getDevice(), 1, &frame.inFlight, VK_TRUE, UINT64_MAX);
    vkResetFences(device.getDevice(), 1, &frame.inFlight);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(
        device.getDevice(),
        swapchain.get(),
        UINT64_MAX,
        frame.imageAvailable,
        VK_NULL_HANDLE,
        &imageIndex
    );

    return imageIndex;
}

void VulkanFrameManager::submitFrame(
    VulkanDevice& device,
    VkQueue graphicsQueue,
    VkCommandBuffer cmd,
    VulkanSwapchain& swapchain,
    uint32_t imageIndex
) {
    auto& frame = frames[currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { frame.imageAvailable };
    VkSemaphore signalSemaphores[] = { frame.renderFinished };

    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmd;

    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, frame.inFlight);

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapchains[] = { swapchain.get() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapchains;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(graphicsQueue, &presentInfo);

    currentFrame = (currentFrame + 1) % maxFrames;
}
