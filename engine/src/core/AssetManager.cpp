#include "engine/core/AssetManager.h"

#include <ranges>
#include <unordered_set>

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

bool AssetManager::AddTexture(std::string_view name, const std::filesystem::path& path)
{
    const auto pathStr = path.string();

    if (!std::filesystem::exists(path))
    {
        spdlog::error("Cannot load texture '{}': file '{}' does not exist", name, pathStr);
        return false;
    }

    if (std::filesystem::is_directory(path))
    {
        spdlog::error("Cannot load texture '{}': path '{}' is a directory, not a file", name, pathStr);
        return false;
    }

    if (!IsValidTextureExtension(path))
    {
        spdlog::error("Cannot load texture '{}': unsupported file format '{}'", name, path.extension().string());
        return false;
    }

    if (path.is_absolute())
        spdlog::warn("Absolute path used for texture '{}': {}", name, pathStr);

    if (m_textures.contains(name))
        spdlog::warn("Texture '{}' already exists and will be replaced with '{}'", name, pathStr);

    m_textures[std::string(name)] = LoadTexture(pathStr.c_str());

    return true;
}

bool AssetManager::AddTexture(const std::string_view name, const std::string_view path)
{
    return AddTexture(name, std::filesystem::path(path));
}

void AssetManager::RemoveTexture(std::string_view name)
{
    if (!m_textures.contains(name))
    {
        spdlog::warn("Tried to remove texture {} that does not exist.", name);
        return;
    }

    m_textures.erase(std::string(name));
}

bool AssetManager::IsValidTextureExtension(const std::filesystem::path& path)
{
    static const std::unordered_set<std::string_view, StringHash, std::equal_to<>> validExtensions = {
        ".png", ".bmp", ".tga", ".jpg", ".gif", ".qoi", ".psd", ".dds", ".hdr", ".ktx", ".astc", ".pkm", ".pvr"};

    std::string extension = path.extension().string();
    std::ranges::transform(extension, extension.begin(), ::tolower);

    return validExtensions.contains(extension);
}
} // namespace engine::core