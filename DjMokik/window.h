
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int w, int h, const std::string& title);
    ~Window();

    bool shouldClose();
    void poll();

    GLFWwindow* get();

private:
    GLFWwindow* handle;
};
