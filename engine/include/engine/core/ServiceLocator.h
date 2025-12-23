#pragma once
#include "Application.h"

namespace engine::core
{

class ServiceLocator
{
public:
    static void SetApp(Application* app);

    static AssetManager& GetAssetManager();
private:
    inline static Application* s_app = nullptr;
};


} // namespace engine::core