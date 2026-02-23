#pragma once
#include "raylib.h"

class PreviewPanel {
public:
    PreviewPanel(float x, float width, float height);

    void SetTexture(Texture2D texture);
    void Clear();

    void Update();
    void Draw();

    bool HasTexture() const;

private:
    void CalculateAutoFit();

    float x;
    float width;
    float height;

    Texture2D texture{};
    bool hasTexture = false;

    float zoom = 1.0f;
};