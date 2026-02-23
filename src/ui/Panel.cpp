#include "Panel.h"

Panel::Panel(float width)
    : width(width) {}

void Panel::Draw()
{
      DrawText("Hikari", 40, 40, 30, RAYWHITE);
    DrawRectangle(
        0,
        0,
        (int)width,
        GetScreenHeight(),
        Color{25, 25, 35, 255}
    );

    DrawRectangleLines(
        width - 1,
        0,
        1,
        GetScreenHeight(),
        Color{50, 50, 70, 255}
    );
}

float Panel::GetWidth() const
{
    return width;
}