#include "PreviewPanel.h"

PreviewPanel::PreviewPanel(float x, float width, float height)
    : x(x),
      width(width),
      height(height),
      fitButton({x + 20, 60, 80, 30}, "Fit"),
      fillButton({x + 110, 60, 80, 30}, "Fill")
{
}

void PreviewPanel::SetTexture(Texture2D tex)
{
    texture = tex;
    hasTexture = true;
    CalculateScale();
}

void PreviewPanel::Clear()
{
    hasTexture = false;
}

void PreviewPanel::CalculateScale()
{
    float innerX = x + 10;
    float innerY = 100;
    float innerWidth = width - 20;
    float innerHeight = height - 120;

    float scaleX = innerWidth / texture.width;
    float scaleY = innerHeight / texture.height;

    if (mode == DisplayMode::Fit)
        scale = (scaleX < scaleY) ? scaleX : scaleY;
    else
        scale = (scaleX > scaleY) ? scaleX : scaleY;
}

void PreviewPanel::Update()
{
    fitButton.Update();
    fillButton.Update();

    if (fitButton.IsClicked()) {
        mode = DisplayMode::Fit;
        if (hasTexture) CalculateScale();
    }

    if (fillButton.IsClicked()) {
        mode = DisplayMode::Fill;
        if (hasTexture) CalculateScale();
    }
}

void PreviewPanel::Draw()
{
    DrawRectangle((int)x, 0, (int)width, (int)height, Color{25,25,35,255});
    DrawRectangle((int)x, 0, 2, (int)height, Color{70,70,90,255});
    DrawText("Preview", (int)x + 20, 20, 26, RAYWHITE);

    fitButton.Draw();
    fillButton.Draw();

    int innerX = (int)x + 10;
    int innerY = 100;
    int innerWidth = (int)width - 20;
    int innerHeight = (int)height - 120;

    DrawRectangleLines(innerX, innerY, innerWidth, innerHeight,
                       Color{60,60,80,255});

    if (!hasTexture)
        return;

    BeginScissorMode(innerX, innerY, innerWidth, innerHeight);

    float scaledWidth = texture.width * scale;
    float scaledHeight = texture.height * scale;

    float centerX = x + width / 2.0f;
    float centerY = innerY + innerHeight / 2.0f;

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

    EndScissorMode();
}

Image PreviewPanel::ExportCurrentView(int outputWidth, int outputHeight)
{
    RenderTexture2D target = LoadRenderTexture(outputWidth, outputHeight);

    BeginTextureMode(target);
    ClearBackground(BLACK);

    float scaleX = (float)outputWidth / texture.width;
    float scaleY = (float)outputHeight / texture.height;

    float finalScale;

    if (mode == DisplayMode::Fit)
        finalScale = (scaleX < scaleY) ? scaleX : scaleY;
    else
        finalScale = (scaleX > scaleY) ? scaleX : scaleY;

    float scaledWidth = texture.width * finalScale;
    float scaledHeight = texture.height * finalScale;

    float centerX = outputWidth / 2.0f;
    float centerY = outputHeight / 2.0f;

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

    EndTextureMode();

    Image result = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&result);

    UnloadRenderTexture(target);

    return result;
}