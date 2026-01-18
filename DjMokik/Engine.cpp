#include "Engine.h"
#include "DemoSceneBuilder.h"

bool Engine::init(Window& window) {

    if (!context.init(window))
        return false;

    if (!renderer.init(context))
        return false;

    // ВАЖНО: вся логика создания контента теперь тут
    DemoSceneBuilder::build(
        scene,
        renderer.getMeshManager(),
        renderer.getContext().getDevice()
    );

    renderer.rebuildRenderObjects(scene);

    return true;
}

void Engine::run(Window& window) {

    while (!window.shouldClose()) {
        window.pollEvents();

        if (scene.isDirty()) {
            renderer.rebuildRenderObjects(scene);
            scene.clearDirty();
        }

        renderer.drawScene(scene);
    }
}


void Engine::cleanup() {
    renderer.cleanup();
    context.cleanup();
}

Scene& Engine::getScene() {
    return scene;
}

VulkanRenderer& Engine::getRenderer() {
    return renderer;
}
