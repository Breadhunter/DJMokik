#include "Scene.h"

Entity& Scene::createEntity(VulkanMesh& mesh) {
    entities.push_back({});
    Entity& e = entities.back();

    e.mesh = &mesh;
    dirty = true;
    return e;
}

std::vector<Entity>& Scene::getEntities() {
    return entities;
}

const std::vector<Entity>& Scene::getEntities() const {
    return entities;
}
