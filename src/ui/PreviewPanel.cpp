#include "PreviewPanel.hpp"

PreviewPanel::PreviewPanel(float x, float width, float height)
    : x(x), width(width), height(height)
{
}

void PreviewPanel::SetTexture(Texture2D tex)
{
    texture = tex;
    hasTexture = true;
    CalculateAutoFit();
}

void PreviewPanel::Clear()
{
    hasTexture = false;
}

void PreviewPanel::CalculateAutoFit()
{
    float padding = 40.0f;

    float availableWidth = width - padding;
    float availableHeight = height - 120.0f;

    float scaleX = availableWidth / texture.width;
    float scaleY = availableHeight / texture.height;

    zoom = (scaleX < scaleY) ? scaleX : scaleY;
}

void PreviewPanel::Update()
{
}

void PreviewPanel::Draw()
{
    DrawRectangle(
        (int)x,
        0,
        (int)width,
        (int)height,
        Color{25, 25, 35, 255}
    );

    DrawRectangleLines(
        (int)x,
        0,
        2,
        (int)height,
        Color{70, 70, 90, 255}
    );

    DrawRectangleLines(
        (int)x + 10,
        60,
        (int)width - 20,
        (int)height - 80,
        Color{60, 60, 80, 255}
    );

    DrawText("Preview",
             (int)x + 20,
             20,
             26,
             RAYWHITE);

    if (!hasTexture)
        return;

    float scaledWidth = texture.width * zoom;
    float scaledHeight = texture.height * zoom;

    float centerX = x + width / 2.0f;
    float centerY = height / 2.0f + 20;

    Rectangle source = {
        0, 0,
        (float)texture.width,
        (float)texture.height
    };

    Rectangle dest = {
        centerX,
        centerY,
        scaledWidth,
        scaledHeight
    };

    Vector2 origin = { scaledWidth / 2.0f, scaledHeight / 2.0f };

    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}