#pragma once
#include <vector>
#include "Entity.h"
#include "Camera.h"

class Scene {
public:
    Entity& createEntity(VulkanMesh& mesh);

    std::vector<Entity>& getEntities();
    const std::vector<Entity>& getEntities() const;

    Camera& getCamera() { return camera; }
    const Camera& getCamera() const { return camera; }

    bool isDirty() const { return dirty; }
    void clearDirty() { dirty = false; }

private:
    std::vector<Entity> entities;
    Camera camera;
    bool dirty = false;
};
