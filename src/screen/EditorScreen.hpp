#pragma once
#include "raylib.h"
#include "../ui/Button.hpp"

class EditorScreen {
public:
    EditorScreen();
    void Update();
    void Draw();

private:
    void LoadWallpaper(const char* path);
    
    Texture2D wallpaperTexture{};
    bool hasWallpaper = false;
    float zoom = 1.0f;
    Vector2 offset = {0, 0};

    bool dragging = false;
    Vector2 lastMousePos = {0, 0};

    // btns
    Button loadBtn1;
    Button loadBtn2;
    Button loadBtn3;
    Button setWallpaperButton;
};