#pragma once
#include "raylib.h"
#include <vector>
#include <string>

class WallpaperGridPanel {
public:
    WallpaperGridPanel(int x, int width, int height);

    void LoadWallpapers(const std::vector<std::string>& paths);
    void Update();
    void Draw();

    bool HasSelection() const;
    Texture2D GetSelectedTexture() const;

private:
    int posX;
    int width;
    int height;

    int columns = 2;
    int padding = 20;
    int thumbSize = 200;

    std::vector<Texture2D> textures;
    int selectedIndex = -1;
};