#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

class VulkanPipeline {
public:
    bool init(VkDevice device, VkRenderPass renderPass);
    void cleanup(VkDevice device);

    VkPipeline get() const { return pipeline; }
    VkPipelineLayout getLayout() const { return layout; }
    VkDescriptorSetLayout getDescriptorSetLayout() const {return descriptorSetLayout;}
    void createGraphicsPipeline() {};

private:
    VkPipeline pipeline = VK_NULL_HANDLE;
    VkPipelineLayout layout = VK_NULL_HANDLE;
    VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
    std::vector<char> readFile(const std::string& filename);
    VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;
};
