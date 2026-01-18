#include "DemoSceneBuilder.h"

void DemoSceneBuilder::build(
    Scene& scene,
    VulkanMeshManager& meshManager,
    VulkanDevice& device
)
{

    std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1,0,0,1}},
    {{ 0.5f, -0.5f, 0.0f}, {0,1,0,1}},
    {{ 0.0f,  0.5f, 0.0f}, {0,0,1,1}}
    };


    // Создадим 5 объектов, смещённых по Z

    for (int i = 0; i < 5; i++) {
        VulkanMesh& mesh = meshManager.createMesh(device, vertices);

        Entity& e = scene.createEntity(mesh);

        e.transform.position = { 0.0f, 0.0f, 0.0f };
    }
}
