#include "engine/core/ServiceLocator.h"

#include <cassert>

void engine::core::ServiceLocator::SetApp(Application* app)
{
    s_app = app;
}
engine::core::AssetManager& engine::core::ServiceLocator::GetAssetManager()
{
    if (s_app == nullptr)
        throw std::runtime_error("ServiceLocator::SetApp must be called before GetAssetManager");

    return s_app->GetAssetManager();
}