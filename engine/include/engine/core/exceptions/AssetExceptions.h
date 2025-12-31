#pragma once
#include "engine/core/exceptions/EngineException.h"

namespace engine::exceptions
{

class AssetNotFoundException : public EngineException
{
public:
    explicit AssetNotFoundException(const std::string_view assetType, const std::string_view assetName, const std::string_view file, const int line)
    : EngineException("AssetManager", std::format("{} '{}' not found.", assetType, assetName), file, line),
    m_type(assetType), m_name(assetName)
    {
    }

    [[nodiscard]] const std::string& GetType() const;

    [[nodiscard]] const std::string& GetName() const;

private:
    std::string m_type;
    std::string m_name;
};

class AssetFileException : public EngineException
{
public:
    explicit AssetFileException(const std::string_view assetType, const std::string_view assetFilePath,
                              const std::string_view message, const std::string_view file, const int line)
    : EngineException("AssetManager", message, file, line),
    m_type(assetType), m_filePath(assetFilePath)
    {
    }

    [[nodiscard]] const std::string& GetType() const
    {
        return m_type;
    };

    [[nodiscard]] const std::string& GetFilePath() const
    {
        return m_filePath;
    };

private:
    std::string m_type;
    std::string m_filePath;
};

class AssetFileNotFoundException : public AssetFileException
{
public:
    explicit AssetFileNotFoundException(const std::string_view assetType, const std::string_view assetFilePath,
                                      const std::string_view file, const int line)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("{} '{}' not found.", assetType, assetFilePath),
        file,
        line)
    {
    }
};

class AssetIsADirectoryException : public AssetFileException
{
public:
    explicit AssetIsADirectoryException(const std::string_view assetType, const std::string_view assetFilePath,
                                      const std::string_view file, const int line)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("{} '{}' not found.", assetType, assetFilePath),
        file,
        line)
    {
    }
};

// Macros for convenience

#define THROW_ASSET_NOT_FOUND(assetType, assetName) \
throw engine::exceptions::AssetNotFoundException(assetType, assetName, __FILE__, __LINE__)

#define THROW_ASSET_FILE_NOT_FOUND(assetType, assetFilePath) \
throw engine::exceptions::AssetFileNotFoundException(assetType, assetFilePath, __FILE__, __LINE__)

} // namespace engine::exceptions
