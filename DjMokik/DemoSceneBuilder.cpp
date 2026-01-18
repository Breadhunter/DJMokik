#include "DemoSceneBuilder.h"

void DemoSceneBuilder::build(
    Scene& scene,
    VulkanMeshManager& meshManager,
    VulkanDevice& device
)
{

    std::vector<Vertex> vertices = {
        {{ 0.0f, -0.2f, 0.0f }, {1.0f, 0.0f, 0.0f, 0.5f}},
        {{ 0.5f,  0.5f, 0.0f }, {0.0f, 1.0f, 0.0f, 0.5f}},
        {{-0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 1.0f, 0.5f}}
    };

    // Создадим 5 объектов, смещённых по Z

    for (int i = 0; i < 5; i++) {

        VulkanMesh& mesh = meshManager.createMesh(device, vertices);

        Entity& e = scene.createEntity(mesh);

        // Сдвигаем каждый следующий чуть дальше
        e.transform.position = {i*0.2f+1, 0.0f, -i * 0.6f };

        // Немного вращаем для наглядности
        e.transform.rotation.y = i * 10.0f;
    }
}
