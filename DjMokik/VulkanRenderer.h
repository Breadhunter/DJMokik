#pragma once

#include "VulkanRenderContext.h"
#include "VulkanMeshManager.h"
#include "VulkanCommandRecorder.h"
#include "VulkanFrameManager.h"
#include "VulkanUniformBuffer.h"
#include "Scene.h"
#include "RenderObject.h"
#include "VulkanDescriptorPool.h"

class VulkanRenderer {
public:
    bool init(VulkanRenderContext& ctx);

    void drawScene(Scene& scene);

    void cleanup();

    void rebuildRenderObjects(const Scene& scene);


    VulkanMeshManager& getMeshManager();

    VulkanRenderContext& getContext() {
        return *context;
    }

private:
    VulkanRenderContext* context = nullptr;

    VulkanMeshManager meshManager;
    VulkanCommandRecorder recorder;
    VulkanFrameManager frameManager;
    std::vector<RenderObject> renderObjects;
    VulkanDescriptorPool descriptorPool;

};
