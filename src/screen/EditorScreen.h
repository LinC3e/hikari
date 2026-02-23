#pragma once
#include "raylib.h"

#include "../ui/Button.h"
#include "../ui/Panel.h"
#include "../ui/PreviewPanel.h"
#include "../ui/WallpaperGridPanel.h"

class EditorScreen {
public:
    EditorScreen();
    void Init();
    void Update();
    void Draw();

private:
    Panel leftPanel;
    WallpaperGridPanel grid;
    PreviewPanel preview;

    Button setWallpaperButton;
};