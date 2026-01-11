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

    void Run();

    AssetManager& GetAssetManager();

    void ProcessLayerActions();

    template <std::derived_from<Layer> T, typename... Args>
    void QueuePushLayer(Args&&... args)
    {
        auto unpackedArgs = std::make_tuple(std::forward<Args>(args)...);

        auto factory = [this, unpackedArgs = std::move(unpackedArgs)]() mutable {
            std::apply(
                [this]<typename... UnpackedArgs>(UnpackedArgs&&... elements) {
                    m_layers.emplace_back(std::make_unique<T>(std::forward<UnpackedArgs>(elements)...));
                },
                std::move(unpackedArgs));
        };

        m_queuedLayerActions.emplace_back(std::move(factory));
    }

private:
    AssetManager m_assetManager{};
    std::vector<std::unique_ptr<Layer>> m_layers{};
    std::vector<std::function<void()>> m_queuedLayerActions;
};

} // namespace engine::core
