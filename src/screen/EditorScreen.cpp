#include "EditorScreen.hpp"
#include "../platform/WindowsWallpaper.hpp"
#include <filesystem>

EditorScreen::EditorScreen()
    : loadBtn1({40, 120, 200, 40}, "Load Test 1"),
      loadBtn2({40, 170, 200, 40}, "Load Test 2"),
      loadBtn3({40, 220, 200, 40}, "Load Test 3"),
      setWallpaperButton({40, 300, 200, 40}, "Set as Wallpaper")
{
}

void EditorScreen::LoadWallpaper(const char* path)
{
    if (hasWallpaper)
        UnloadTexture(wallpaperTexture);

    wallpaperTexture = LoadTexture(path);
    hasWallpaper = true;

    zoom = 1.0f;
    offset = {0, 0};
}

void EditorScreen::Update()
{
    // ----------------------
    // Update btns
    // ----------------------
    loadBtn1.Update();
    loadBtn2.Update();
    loadBtn3.Update();
    setWallpaperButton.Update();

    if (loadBtn1.IsClicked())
        LoadWallpaper("../../assets/images/test.jpg");

    if (loadBtn2.IsClicked())
        LoadWallpaper("../../assets/images/test2.jpg");

    if (loadBtn3.IsClicked())
        LoadWallpaper("../../assets/images/test3.jpg");

    if (!hasWallpaper)
        return;

    // ----------------------
    // Zoom
    // ----------------------
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f) {
        zoom += wheel * 0.1f;
        if (zoom < 0.1f) zoom = 0.1f;
    }

    // ----------------------
    // Drag
    // ----------------------
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

    // ----------------------
    // Set Wallpaper
    // ----------------------
    if (setWallpaperButton.IsClicked()) {

        Image img = LoadImageFromTexture(wallpaperTexture);
        ExportImage(img, "output.png");
        UnloadImage(img);

        std::wstring absolutePath =
            std::filesystem::absolute("output.png").wstring();

        WindowsWallpaper::SetWallpaper(absolutePath);
    }
}

void EditorScreen::Draw()
{
    ClearBackground({18, 18, 25, 255});

    DrawText("Hikari - Wallpaper Editor", 40, 40, 30, RAYWHITE);

    loadBtn1.Draw();
    loadBtn2.Draw();
    loadBtn3.Draw();
    setWallpaperButton.Draw();

    if (!hasWallpaper)
        return;

    float width = wallpaperTexture.width * zoom;
    float height = wallpaperTexture.height * zoom;

    Rectangle source = {
        0, 0,
        (float)wallpaperTexture.width,
        (float)wallpaperTexture.height
    };

    Rectangle dest = {
        GetScreenWidth()/2.0f + offset.x,
        GetScreenHeight()/2.0f + offset.y,
        width,
        height
    };

    Vector2 origin = { width/2.0f, height/2.0f };

    DrawTexturePro(
        wallpaperTexture,
        source,
        dest,
        origin,
        0.0f,
        WHITE
    );
}