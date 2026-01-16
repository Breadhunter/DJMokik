#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window();
    ~Window();

    bool init(int width, int height, const std::string& title);
    void cleanup();
    bool shouldClose();
    void pollEvents();

    GLFWwindow* get() { return window; }

private:
    GLFWwindow* window = nullptr;
};
