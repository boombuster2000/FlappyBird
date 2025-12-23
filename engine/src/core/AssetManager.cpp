#include "engine/core/AssetManager.h"

#include <ranges>

// ReSharper disable once CppUnusedIncludeDirective
#include "engine/Platform.h"
#include "spdlog/spdlog.h"

namespace engine::core
{

AssetManager::~AssetManager()
{
    for (const auto& texture : m_textures | std::views::values)
        UnloadTexture(texture);

    m_textures.clear();
}

void AssetManager::AddTexture(const std::string_view name, const std::string_view path)
{
    if (m_textures.contains(name.data()))
        spdlog::warn("Texture {} already exists and is being replaced.", name);

    m_textures[std::string(name)] = LoadTexture(path.data());
}

void AssetManager::RemoveTexture(std::string_view name)
{
    if (!m_textures.contains(name.data()))
    {
        spdlog::warn("Tried to remove texture {} that does not exist.", name);
        return;
    }

    m_textures.erase(name.data());
}

} // namespace engine::core