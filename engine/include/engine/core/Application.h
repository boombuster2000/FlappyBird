#pragma once

#include <vector>

#include "engine/core/AppSpec.h"
#include "engine/core/AssetManager.h"
#include "engine/core/Layer.h"

namespace engine::core
{

class Application
{
public:
    explicit Application(const AppSpec& appSpec);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Run() const;

    AssetManager& GetAssetManager();

    template <std::derived_from<Layer> T, typename... Args>
    T* PushLayer(Args&&... args)
    {
        auto& layer = m_layers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast<T*>(layer.get());
    }

private:
    AssetManager m_assetManager{};
    std::vector<std::unique_ptr<Layer>> m_layers{};
};

} // namespace engine::core
