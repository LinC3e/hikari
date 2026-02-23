#pragma once
#include "raylib.h"
#include <string>

class Button {
public:
    Button(Rectangle bounds, const std::string& text);

    void Update();
    void Draw();

    bool IsClicked() const;

private:
    Rectangle bounds;
    std::string text;

    bool hovered = false;
    bool clicked = false;
};