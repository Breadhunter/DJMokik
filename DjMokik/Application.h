#pragma once
#include "Window.h"
#include "Engine.h"

class Application {
public:
    bool init();
    void run();
    void cleanup();

private:
    Window window;
    Engine engine;
};
