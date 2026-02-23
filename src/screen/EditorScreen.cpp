#include <filesystem>
#include "EditorScreen.h"
#include "../platform/WindowsWallpaper.h"

EditorScreen::EditorScreen()
    : leftPanel(280),
      preview(280, 500, 280),
      loadBtn1({40, 120, 200, 40}, "Load Test 1"),
      loadBtn2({40, 170, 200, 40}, "Load Test 2"),
      loadBtn3({40, 220, 200, 40}, "Load Test 3"),
      setWallpaperButton({40, 300, 200, 40}, "Set as Wallpaper")
{
}

void EditorScreen::LoadWallpaper(const char *path)
{
  if (hasWallpaper)
    UnloadTexture(wallpaperTexture);

  wallpaperTexture = LoadTexture(path);
  hasWallpaper = true;

  preview.SetTexture(wallpaperTexture);
}

void EditorScreen::Update()
{
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

  preview.Update();

  if (setWallpaperButton.IsClicked() && hasWallpaper)
  {
    int monitorWidth = GetMonitorWidth(0);
    int monitorHeight = GetMonitorHeight(0);

    Image img = preview.ExportCurrentView(monitorWidth, monitorHeight);

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

  leftPanel.Draw();
  DrawText("Hikari", 40, 40, 28, RAYWHITE);

  loadBtn1.Draw();
  loadBtn2.Draw();
  loadBtn3.Draw();
  setWallpaperButton.Draw();

  preview.Draw();
}