#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>

#include "raylib.h"

#include "engine/StringHash.h"

namespace engine::core
{

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager();

    void Initialize();

    /// @brief Loads the texture into memory.
    /// @param name Identifier used to retrieve this texture later.
    /// @param path File path to the texture image.
    /// @return true if the texture was successfully loaded; false otherwise.
    /// @warning If a texture with this name already exists, it will be replaced.
    bool AddTexture(std::string_view name, const std::filesystem::path& path);

    /// @brief Unloads texture from memory.
    /// @param name The texture identifier
    /// @note Invalidates any existing pointers/references to this texture.
    ///       Does nothing if the texture is not found.
    void RemoveTexture(std::string_view name);

    const Texture2D& GetTexture(std::string_view name) const;


private:
    static bool IsValidTextureExtension(const std::filesystem::path& path);

private:
    bool m_isInitialized = false;
    Texture2D m_fallbackTexture;
    std::unordered_map<std::string, Texture2D, StringHash, StringEqual> m_textures{};
};

} // namespace engine::core
