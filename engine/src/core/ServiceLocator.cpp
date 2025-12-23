#include "engine/core/ServiceLocator.h"

void engine::core::ServiceLocator::SetApp(Application* app)
{
    s_app = app;
}
engine::core::AssetManager& engine::core::ServiceLocator::GetAssetManager()
{
    return s_app->GetAssetManager();
}