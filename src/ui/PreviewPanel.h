#pragma once
#include "raylib.h"
#include "Button.h"

class PreviewPanel {
public:
    enum class DisplayMode {
        Fit,
        Fill
    };

    PreviewPanel(float x, float width, float height);
    Image ExportCurrentView(int outputWidth, int outputHeight);
    void SetTexture(Texture2D texture);
    
    void Clear();
    void Update();
    void Draw();

private:
    void CalculateScale();
    float x;
    float width;
    float height;

    Texture2D texture{};
    bool hasTexture = false;

    float scale = 1.0f;
    DisplayMode mode = DisplayMode::Fit;

    Button fitButton;
    Button fillButton;
};