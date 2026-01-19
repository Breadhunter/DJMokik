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


    VulkanMesh& mesh = meshManager.createMesh(device, vertices);

    for (int i = 0; i < 5; i++) {
        

        Entity& e = scene.createEntity(mesh);

        e.transform.position = { i*0.3f, 0.0f, 0.0f };
    }
}
