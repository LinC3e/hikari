#include "EditorScreen.hpp"
#include "../platform/WindowsWallpaper.hpp"
#include <filesystem>

EditorScreen::EditorScreen() {}

void EditorScreen::Update() {

    if (IsKeyPressed(KEY_L)) {
        wallpaperTexture = LoadTexture("../../assets/images/test.jpg");
        hasWallpaper = true;
        zoom = 1.0f;
        offset = {0, 0};
    }

    if (!hasWallpaper) return;

    // Zoom
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f) {
        zoom += wheel * 0.1f;
        if (zoom < 0.1f) zoom = 0.1f;
    }

    // Drag
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        dragging = true;
        lastMousePos = GetMousePosition();
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        dragging = false;
    }

    if (dragging) {
        Vector2 mouse = GetMousePosition();
        offset.x += mouse.x - lastMousePos.x;
        offset.y += mouse.y - lastMousePos.y;
        lastMousePos = mouse;
    }

    // Botón Set Wallpaper
    if (CheckCollisionPointRec(GetMousePosition(), setButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        Image img = LoadImageFromTexture(wallpaperTexture);
        ExportImage(img, "output.png");
        UnloadImage(img);

        std::wstring absolutePath =
            std::filesystem::absolute("output.png").wstring();

        WindowsWallpaper::SetWallpaper(absolutePath);
    }
}

void EditorScreen::Draw() {

    ClearBackground({18, 18, 25, 255});

    DrawText("Hikari - Wallpaper Editor", 40, 40, 30, RAYWHITE);
    DrawText("Press L to load test wallpaper", 40, 80, 18, GRAY);

    // Botón
    DrawRectangleRec(setButton, DARKGRAY);
    DrawText("Set as Wallpaper",
             setButton.x + 20,
             setButton.y + 10,
             20,
             RAYWHITE);

    if (!hasWallpaper) return;

    float width = wallpaperTexture.width * zoom;
    float height = wallpaperTexture.height * zoom;

    Rectangle source = {0, 0,
                        (float)wallpaperTexture.width,
                        (float)wallpaperTexture.height};

    Rectangle dest = {
        GetScreenWidth()/2.0f + offset.x,
        GetScreenHeight()/2.0f + offset.y,
        width,
        height
    };

    Vector2 origin = { width/2.0f, height/2.0f };

    DrawTexturePro(wallpaperTexture,
                   source,
                   dest,
                   origin,
                   0.0f,
                   WHITE);
}