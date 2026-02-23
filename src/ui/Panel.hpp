#pragma once
#include "raylib.h"

class Panel {
public:
    Panel(float width);

    void Draw();
    float GetWidth() const;

private:
    float width;
};