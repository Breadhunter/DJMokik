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

    for (int i = 0; i < 88; i++) {
        

        Entity& e = scene.createEntity(mesh);

        e.transform.position = { 0.0f, 0.0f, 0.1f };
		e.transform.rotation = { i * 1.0f, i * 1.0f, i * 1.0f };
    }
}
