#include <filesystem>
#include "EditorScreen.h"
#include "../platform/WindowsWallpaper.h"

EditorScreen::EditorScreen()
    : leftPanel(280),
      grid(280, 800, 720),
      preview(1077, 200, 300),
      setWallpaperButton({40, 100, 200, 40}, "Set as Wallpaper")
{
}

void EditorScreen::Init()
{
    grid.LoadWallpapers({
        "../../assets/images/test.jpg",
        "../../assets/images/test2.jpg",
        "../../assets/images/test3.jpg"
    });
}

void EditorScreen::Update()
{
    grid.Update();
    preview.Update();
    setWallpaperButton.Update();

    if (grid.HasSelection())
    {
        preview.SetTexture(grid.GetSelectedTexture());
    }

    if (setWallpaperButton.IsClicked() && grid.HasSelection())
    {
        Image img = preview.ExportCurrentView(1920, 1080);

        ExportImage(img, "output.png");
        UnloadImage(img);

        std::wstring path =
            std::filesystem::absolute("output.png").wstring();

        WindowsWallpaper::SetWallpaper(path);
    }
}

void EditorScreen::Draw()
{
    ClearBackground({18, 18, 25, 255});

    leftPanel.Draw();
    grid.Draw();
    preview.Draw();

    DrawText("Hikari", 40, 40, 28, RAYWHITE);
    setWallpaperButton.Draw();
}