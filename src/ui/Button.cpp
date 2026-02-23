#include "Button.h"

Button::Button(Rectangle bounds, const std::string& text)
    : bounds(bounds), text(text) {}

void Button::Update() {
    hovered = CheckCollisionPointRec(GetMousePosition(), bounds);

    clicked = false;
    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        clicked = true;
    }
}

bool Button::IsClicked() const {
    return clicked;
}

void Button::Draw() {

    Color bgColor = hovered ? Color{60,60,80,255}
                            : Color{40,40,55,255};

    DrawRectangleRec(bounds, bgColor);
    DrawRectangleLinesEx(bounds, 1, DARKGRAY);

    int fontSize = 20;
    int textWidth = MeasureText(text.c_str(), fontSize);

    DrawText(
        text.c_str(),
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        RAYWHITE
    );
}