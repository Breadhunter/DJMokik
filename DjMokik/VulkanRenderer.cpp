#include "VulkanRenderer.h"
#include <iostream>

bool VulkanRenderer::init(VulkanRenderContext& ctx) {

    context = &ctx;

    if (!meshManager.init(ctx.getDevice())) {
        std::cerr << "Failed to init mesh manager\n";
        return false;
    }

    recorder.init(ctx.getCommand());

    frameManager.init(ctx.getDevice(), 2);


    return true;
}

void VulkanRenderer::drawScene(Scene& scene) {

    if (renderObjects.empty()) {
        return;
    }

    uint32_t imageIndex = frameManager.beginFrame(
        context->getDevice(),
        context->getSwapchain()
    );

    float aspect =
        context->getSwapchain().getExtent().width /
        (float)context->getSwapchain().getExtent().height;

    for (size_t i = 0; i < scene.getEntities().size(); ++i) {

        Entity& entity = scene.getEntities()[i];

        if (!entity.mesh)
            continue;

        RenderObject& ro = renderObjects[i];

        UniformBufferObject ubo{};

        ubo.model = entity.transform.getMatrix();
        ubo.view = scene.getCamera().getViewMatrix();
        ubo.proj = scene.getCamera().getProjectionMatrix(aspect);

        ro.ubo.update(context->getDevice(), ubo);
    }

    recorder.recordScene(
        context->getSwapchain(),
        context->getPipeline(),
        renderObjects
    );

    frameManager.submitFrame(
        context->getDevice(),
        context->getDevice().getGraphicsQueue(),
        context->getCommand().getCommandBuffer(imageIndex),
        context->getSwapchain(),
        imageIndex
    );
}



void VulkanRenderer::cleanup() {

    meshManager.cleanup(context->getDevice().getDevice());

    frameManager.cleanup(context->getDevice().getDevice());
}

VulkanMeshManager& VulkanRenderer::getMeshManager() {
    return meshManager;
}

void VulkanRenderer::rebuildRenderObjects(const Scene& scene) {

    renderObjects.clear();

    for (const Entity& e : scene.getEntities()) {

        if (!e.mesh)
            continue;

        RenderObject ro;
        ro.mesh = e.mesh;

        ro.ubo.init(context->getDevice());

        renderObjects.push_back(std::move(ro));
    }
}
