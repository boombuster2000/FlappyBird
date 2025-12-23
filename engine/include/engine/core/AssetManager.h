#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

namespace engine::core
{

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager();

    /// @brief Loads the texture into memory.
    /// @param name Identifier used to retrieve this texture later.
    /// @param path File path to the texture image.
    /// @warning If a texture with this name already exists, it will be replaced.
    void AddTexture(std::string_view name, std::string_view path);

    /// @brief Unloads texture from memory.
    /// @param name The texture identifier
    /// @note Invalidates any existing pointers/references to this texture.
    ///       Does nothing if the texture is not found.
    void RemoveTexture(std::string_view name);

private:
    std::unordered_map<std::string, Texture2D> m_textures{};
};
} // namespace engine::core
