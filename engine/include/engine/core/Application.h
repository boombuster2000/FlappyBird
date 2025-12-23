#pragma once

#include "engine/core/AppSpec.h"
#include "engine/core/AssetManager.h"

namespace engine::core
{

class Application
{
public:
    explicit Application(const AppSpec& appSpec);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Run();

    AssetManager& GetAssetManager();

private:
    AssetManager m_assetManager{};
};

} // namespace engine::core
