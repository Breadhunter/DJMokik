#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in float height;

layout(location = 0) out vec4 outColor;

void main() {

    // Цвет меняется от высоты волны и позиции
    vec3 baseColor = vec3(
        0.5 + 0.5 * sin(fragPos.x * 3.0),
        0.5 + 0.5 * cos(fragPos.y * 3.0),
        0.8 + height * 2.0
    );

    outColor = vec4(baseColor, 1.0);
}
