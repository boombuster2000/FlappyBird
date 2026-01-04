#include "engine/core/AssetManager.h"

#include <ranges>
#include <unordered_set>

#include "spdlog/spdlog.h"

namespace engine::core
{

AssetManager::~AssetManager()
{
    for (const auto& texture : m_textures | std::views::values)
        UnloadTexture(texture);

    m_textures.clear();

    if (m_isInitialized)
        UnloadTexture(m_fallbackTexture);
}

void AssetManager::Initialize()
{
    if (m_isInitialized) return;

    const Image img = GenImageChecked(64, 64, 8, 8, MAGENTA, BLACK);
    m_fallbackTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    m_isInitialized = true;
}

bool AssetManager::AddTexture(std::string_view name, const std::filesystem::path& path)
{
    assert(m_isInitialized);

    const auto pathStr = path.string();

    if (!std::filesystem::exists(path))
    {
        spdlog::error("[AssetManager] - Cannot load texture '{}': file '{}' does not exist", name, pathStr);
        return false;
    }

    if (std::filesystem::is_directory(path))
    {
        spdlog::error("[AssetManager] - Cannot load texture '{}': path '{}' is a directory, not a file", name, pathStr);
        return false;
    }

    if (!IsValidTextureExtension(path))
    {
        spdlog::error("[AssetManager] - Cannot load texture '{}': unsupported file format '{}'", name, path.extension().string());
        return false;
    }

    if (path.is_absolute())
        spdlog::warn("[AssetManager] - Absolute path used for texture '{}': {}", name, pathStr);

    if (m_textures.contains(name))
    {
        spdlog::warn("[AssetManager] - Texture '{}' already exists and will be replaced with '{}'", name, pathStr);
        UnloadTexture(m_textures.at(std::string(name)));
    }

    m_textures[std::string(name)] = LoadTexture(pathStr.c_str());

    return true;
}

void AssetManager::RemoveTexture(std::string_view name)
{
    assert(m_isInitialized);
    const auto it = m_textures.find(name);
    if (it == m_textures.end())
    {
        spdlog::warn("[AssetManager] - Tried to remove texture {} that does not exist.", name);
        return;
    }

    UnloadTexture(it->second);
    m_textures.erase(it);
}

const Texture2D& AssetManager::GetTexture(std::string_view name) const
{
    assert(m_isInitialized);

    if (const auto it = m_textures.find(name); it != m_textures.end())
    {
        return it->second;
    }

    spdlog::error("[AssetManager] - Texture '{}' not found, using fallback", name);
    return m_fallbackTexture;
}

bool AssetManager::IsValidTextureExtension(const std::filesystem::path& path)
{
    static const std::unordered_set<std::string_view, StringHash, std::equal_to<>> validExtensions = {
        ".png", ".bmp", ".tga", ".jpg", ".gif", ".qoi", ".psd", ".dds", ".hdr", ".ktx", ".astc", ".pkm", ".pvr"};

    std::string extension = path.extension().string();
    std::ranges::transform(extension, extension.begin(), [](const unsigned char c) { return std::tolower(c); });

    return validExtensions.contains(extension);
}
bool AssetManager::IsInitialized() const
{
    return m_isInitialized;
}

} // namespace engine::core