
#include "window.h"

Window::Window(int w, int h, const std::string& title) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    handle = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
}

Window::~Window() {
    glfwDestroyWindow(handle);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(handle);
}

void Window::poll() {
    glfwPollEvents();
}

GLFWwindow* Window::get() {
    return handle;
}
