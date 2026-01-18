#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position{ 0.0f, 0.0f, 2.0f };
    glm::vec3 rotation{ 0.0f };

    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspect) const;
};
