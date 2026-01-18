#include "Engine.h"
#include "DemoSceneBuilder.h"
#include <iostream>

bool Engine::init(Window& window) {

    std::cout << "Engine init start\n";

    if (!context.init(window)) {
        std::cout << "context.init failed\n";
        return false;
    }

    std::cout << "context.init OK\n";

    if (!renderer.init(context)) {
        std::cout << "renderer.init failed\n";
        return false;
    }

    std::cout << "renderer.init OK\n";

    DemoSceneBuilder::build(
        scene,
        renderer.getMeshManager(),
        renderer.getContext().getDevice()
    );

    std::cout << "Scene built\n";

    renderer.rebuildRenderObjects(scene);

    std::cout << "Render objects rebuilt\n";

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
