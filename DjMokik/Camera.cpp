#include "Camera.h"

glm::mat4 Camera::getViewMatrix() const {

    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.x, { 1,0,0 });
    rot = glm::rotate(rot, rotation.y, { 0,1,0 });
    rot = glm::rotate(rot, rotation.z, { 0,0,1 });

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), -position);

    return rot * trans;
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const {

    return glm::perspective(
        glm::radians(fov),
        aspect,
        nearPlane,
        farPlane
    );
}
