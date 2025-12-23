#include "engine/core/Application.h"
#include "raylib.h"

namespace engine::core
{

Application::Application(const AppSpec& appSpec)
{
    InitWindow(appSpec.width, appSpec.height, appSpec.windowTitle.c_str());

}

Application::~Application()
{
    CloseWindow();
}

void Application::Run()
{
    // Main game loop
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

}

AssetManager& Application::GetAssetManager()
{
    return m_assetManager;
}

} // namespace engine::core