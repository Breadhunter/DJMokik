#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspect) const;

private:
    glm::vec3 position{ 0.0f, 0.0f, 3.0f };
    glm::vec3 front{ 0.0f, 0.0f, -1.0f };
    glm::vec3 up{ 0.0f, 1.0f, 0.0f };

    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
};
