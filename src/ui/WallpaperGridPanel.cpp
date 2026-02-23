#include "WallpaperGridPanel.h"

WallpaperGridPanel::WallpaperGridPanel(int x, int w, int h)
    : posX(x), width(w), height(h)
{
}

void WallpaperGridPanel::LoadWallpapers(const std::vector<std::string>& paths)
{
    textures.clear();

    for (const auto& path : paths)
    {
        TraceLog(LOG_INFO, path.c_str());

        Texture2D tex = LoadTexture(path.c_str());

        if (tex.id == 0)
        {
            TraceLog(LOG_ERROR, "FAILED TO LOAD");
        }
        else
        {
            TraceLog(LOG_INFO, "LOADED OK");
            textures.push_back(tex);
        }
    }
}

void WallpaperGridPanel::Update()
{
    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < textures.size(); i++)
    {
        int col = i % columns;
        int row = i / columns;

        float x = posX + padding + col * (thumbSize + padding);
        float y = 80 + row * (thumbSize + padding);

        Rectangle rect = { x, y, (float)thumbSize, (float)thumbSize };

        if (CheckCollisionPointRec(mouse, rect) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            selectedIndex = i;
        }
    }
}

void WallpaperGridPanel::Draw()
{
    // Fondo panel centro
    DrawRectangleLines(posX, 0, width, height, RED);
    DrawRectangle(posX, 0, width, height, {30, 30, 40, 255});

    DrawText("Wallpapers", posX + 20, 30, 22, RAYWHITE);

    for (int i = 0; i < textures.size(); i++)
    {
        int col = i % columns;
        int row = i / columns;

        float x = posX + padding + col * (thumbSize + padding);
        float y = 80 + row * (thumbSize + padding);

        Rectangle dest = { x, y, (float)thumbSize, (float)thumbSize };

        DrawTexturePro(
            textures[i],
            { 0, 0,
              (float)textures[i].width,
              (float)textures[i].height },
            dest,
            {0, 0},
            0,
            WHITE
        );

        // Borde selección
        if (i == selectedIndex)
        {
            DrawRectangleLinesEx(dest, 3, GREEN);
        }
    }
}

bool WallpaperGridPanel::HasSelection() const
{
    return selectedIndex >= 0;
}

Texture2D WallpaperGridPanel::GetSelectedTexture() const
{
    return textures[selectedIndex];
}