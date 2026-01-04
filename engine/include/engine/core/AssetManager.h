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

    /// @brief Initialises the asset manager and creates the default fallback texture
    ///
    /// This function sets up the asset management system and generates a magenta/black
    /// checkerboard texture used as a placeholder when requested assets fail to load.
    ///
    /// @note Must be called after InitWindow() and before any asset loading operations.
    /// @note The fallback texture is automatically used when GetTexture() fails.
    ///
    /// @warning Calling this function before window initialisation will cause errors
    ///          as texture creation requires an active OpenGL context.
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

    /// @brief Retrieves a texture by its name
    ///
    /// @param name The identifier used when the texture was loaded.
    /// @return A const reference to the texture, or the fallback texture if not found.
    ///
    /// @note If the texture name doesn't exist, returns the magenta/black checkerboard fallback
    ///       texture instead of crashing. Check logs for missing texture warnings.
    /// @note The returned reference remains valid until the asset manager is destroyed.
    ///
    /// @see LoadTexture() for registering textures with names
    const Texture2D& GetTexture(std::string_view name) const;


private:
    static bool IsValidTextureExtension(const std::filesystem::path& path);

private:
    bool m_isInitialized = false;
    Texture2D m_fallbackTexture;
    std::unordered_map<std::string, Texture2D, StringHash, StringEqual> m_textures{};
};

} // namespace engine::core
