#pragma once
#include "engine/core/exceptions/EngineException.h"

namespace engine::exceptions
{

class AssetNotFoundException : public EngineException
{
public:
    AssetNotFoundException(std::string assetType, std::string assetName, const char* file, const int line)
    : EngineException("AssetManager", std::move(std::format("{} '{}' not found.", assetType, assetName)), file, line),
    m_type(std::move(assetType)), m_name(std::move(assetName))
    {
    }

    [[nodiscard]] const std::string& GetType() const;

    [[nodiscard]] const std::string& GetName() const;

private:
    std::string m_type;
    std::string m_name;
};

class AssetFileNotFoundException : public EngineException
{
public:
    AssetFileNotFoundException(std::string assetType, std::string assetFilePath, const char* file, const int line)
    : EngineException("AssetManager", std::move(std::format("{} '{}' not found.", assetType, assetFilePath)), file, line)
    {
    }

    [[nodiscard]] const std::string& GetType() const;

    [[nodiscard]] const std::string& GetFilePath() const;

private:
    std::string m_type;
    std::string m_filePath;
};

// Macros for convenience

#define THROW_ASSET_NOT_FOUND(assetType, assetName) \
throw engine::exceptions::AssetNotFoundException(assetType, assetName, __FILE__, __LINE__)

#define THROW_ASSET_FILE_NOT_FOUND(assetType, assetFilePath) \
throw engine::exceptions::AssetFileNotFoundException(assetType, assetFilePath, __FILE__, __LINE__)

} // namespace engine::exceptions
