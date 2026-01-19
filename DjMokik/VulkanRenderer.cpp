#include "VulkanRenderer.h"
#include <iostream>
#include "VulkanDescriptorSetUtils.h"

bool VulkanRenderer::init(VulkanRenderContext& ctx) {

    context = &ctx;

    if (!meshManager.init(ctx.getDevice())) {
        std::cerr << "Failed to init mesh manager\n";
        return false;
    }

    recorder.init(ctx.getCommand());

    frameManager.init(ctx.getDevice(), 2);

    descriptorPool.init(ctx.getDevice(), 100);


    return true;
}

void VulkanRenderer::drawScene(Scene& scene) {

    // Если количество объектов изменилось – пересобрать renderObjects
    if (renderObjects.size() != scene.getEntities().size()) {
        rebuildRenderObjects(scene);
    }

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

    size_t renderIndex = 0;

    for (size_t i = 0; i < scene.getEntities().size(); ++i) {

        Entity& entity = scene.getEntities()[i];

        if (!entity.mesh)
            continue;

        RenderObject& ro = renderObjects[renderIndex++];

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

    uint32_t objectCount = scene.getEntities().size();

    descriptorPool.cleanup(context->getDevice().getDevice());
    descriptorPool.init(context->getDevice(), objectCount);


    for (const Entity& e : scene.getEntities()) {

        if (!e.mesh)
            continue;

        RenderObject ro;
        ro.mesh = e.mesh;

        ro.ubo.init(context->getDevice());

        ro.descriptorSet = descriptorPool.allocateDescriptorSet(
            context->getDevice().getDevice(),
            context->getPipeline().getDescriptorSetLayout()
        );

        descriptorPool.updateDescriptorSet(
            context->getDevice().getDevice(),
            ro.descriptorSet,
            ro.ubo.getBuffer(),
            sizeof(UniformBufferObject)
        );


        renderObjects.push_back(std::move(ro));
    }
}


