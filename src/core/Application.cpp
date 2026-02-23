#include "Application.hpp"
#include "raylib.h"

Application::Application() {}

void Application::Init() {
    InitWindow(screenWidth, screenHeight, "Hikari");
    SetTargetFPS(60);
}

void Application::Run() {
    Init();

    while (!WindowShouldClose()) {
        Update();

        BeginDrawing();
        ClearBackground(BLACK);

        Draw();

        EndDrawing();
    }

    Shutdown();
}

void Application::Update() {
    editor.Update();
}

void Application::Draw() {
    editor.Draw();
}

void Application::Shutdown() {
    CloseWindow();
}