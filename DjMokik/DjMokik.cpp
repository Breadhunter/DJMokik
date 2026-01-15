#include "window.h"
#include "VulkanContext.h"

int main() {
    Window window(800, 600, "Vulkan Modular");

    VulkanContext context(window.get());

    while (!window.shouldClose()) {
        window.poll();
        context.draw();
    }

    context.waitIdle();
}
