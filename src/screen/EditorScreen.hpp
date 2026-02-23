#pragma once
#include "raylib.h"

class EditorScreen {
public:
    EditorScreen();
    void Update();
    void Draw();

private:
    Texture2D wallpaperTexture{};
    bool hasWallpaper = false;

    float zoom = 1.0f;
    Vector2 offset = {0, 0};

    bool dragging = false;
    Vector2 lastMousePos = {0, 0};

    Rectangle setButton = {40, 120, 220, 40};
};