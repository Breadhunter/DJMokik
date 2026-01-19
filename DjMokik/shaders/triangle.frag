#version 450

layout(location = 0) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

// маленький uniform с временем
layout(push_constant) uniform Push {
    float time;
} push;

void main() {

    // Делаем цвет зависимым от позиции и времени
    float r = sin(fragPos.x * 2.0 + push.time) * 0.5 + 0.5;
    float g = sin(fragPos.y * 2.0 + push.time * 1.3) * 0.5 + 0.5;
    float b = sin(fragPos.z * 2.0 + push.time * 0.7) * 0.5 + 0.5;

    outColor = vec4(r, g, b, 1.0);
}
