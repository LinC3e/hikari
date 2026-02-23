#include "../screen/EditorScreen.h"
#pragma once

class Application {
public:
    Application();
    void Run();

private:
    void Init();
    void Update();
    void Draw();
    void Shutdown();
    EditorScreen editor;

    const int screenWidth = 1280;
    const int screenHeight = 720;
};