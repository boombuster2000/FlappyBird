#include "engine/core/Application.h"
#include "raylib.h"

namespace engine::core
{

Application::Application(const AppSpec& appSpec)
{
    InitWindow(appSpec.width, appSpec.height, appSpec.windowTitle.c_str());
    m_assetManager.Initialize();
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
        ProcessLayerActions();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto& layer : m_layers)
        {
            if (layer->GetState() == LayerState::ACTIVE)
                layer->OnUpdate();

            if (layer->GetVisibility() == LayerVisibility::VISIBLE)
                layer->OnRender();
        }

        EndDrawing();
    }
}

AssetManager& Application::GetAssetManager()
{
    return m_assetManager;
}

void Application::ProcessLayerActions()
{
    for (const auto& factory : m_queuedLayerActions)
        factory();

    m_queuedLayerActions.clear();
}

} // namespace engine::core