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

}

void Application::Draw() {
    DrawText("Hikari", 50, 50, 40, RAYWHITE);
    DrawText("Hola mundo 🌸", 50, 120, 20, LIGHTGRAY);
}

void Application::Shutdown() {
    CloseWindow();
}