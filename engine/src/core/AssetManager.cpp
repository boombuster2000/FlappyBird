#include "engine/core/AssetManager.h"

#include <ranges>
#include <unordered_set>

#include "spdlog/spdlog.h"

#include "engine/core/exceptions/AssetExceptions.h"


namespace engine::core
{

AssetManager::~AssetManager()
{
    for (const auto& texture : m_textures | std::views::values)
        UnloadTexture(texture);

    m_textures.clear();
}

void AssetManager::AddTexture(std::string_view name, const std::filesystem::path& path)
{
    const auto pathStr = path.string();

    if (!std::filesystem::exists(path))
        THROW_ASSET_FILE_NOT_FOUND("texture", path.string());

    if (std::filesystem::is_directory(path))
        THROW_ASSET_FILE_IS_A_DIRECTORY("texture", path.string());

    if (!IsValidTextureExtension(path))
        THROW_INVALID_ASSET_FILE_EXTENSION("texture", path.string());

    if (path.is_absolute())
        spdlog::warn("Absolute path used for texture '{}': {}", name, pathStr);

    if (m_textures.contains(name))
        spdlog::warn("Texture '{}' already exists and will be replaced with '{}'", name, pathStr);

    m_textures[std::string(name)] = LoadTexture(pathStr.c_str());

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

const Texture2D& AssetManager::GetTexture(const std::string& name) const
{
    if (!m_textures.contains(name))
        THROW_ASSET_NOT_FOUND("texture", name);

    return m_textures.at(name);
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