#pragma once
#include "Scene.h"
#include "VulkanMeshManager.h"
#include "Vertex.h"

class DemoSceneBuilder {
public:
    static void build(
        Scene& scene,
        VulkanMeshManager& meshManager,
        VulkanDevice& device
    );
};

