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
        std::format("Failed to find {} file '{}'.", assetType, assetFilePath),
        file,
        line)
    {
    }
};

class AssetPathIsADirectoryException : public AssetFileException
{
public:
    explicit AssetPathIsADirectoryException(const std::string_view assetType, const std::string_view assetFilePath,
                                      const std::string_view file, const int line)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("{} filepath '{}' is a directory.", assetType, assetFilePath),
        file,
        line)
    {
    }
};

class InvalidAssetFileExtension : public AssetFileException
{
public:
    explicit InvalidAssetFileExtension(const std::string_view assetType, const std::string_view assetFilePath,
                                      const std::string_view file, const int line)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("Unsupported {} file format '{}'.", assetType, std::filesystem::path(file).extension().string()),
        file,
        line)
    {
        const std::filesystem::path path = assetFilePath;
        m_extension = path.extension().string();
    }

    [[nodiscard]] const std::string& GetExtension() const
    {
        return m_extension;
    }

private:
    std::string m_extension;
};

// Macros for convenience
#define THROW_ASSET_NOT_FOUND(assetType, assetName) \
throw engine::exceptions::AssetNotFoundException(assetType, assetName, __FILE__, __LINE__)

#define THROW_ASSET_FILE_NOT_FOUND(assetType, assetFilePath) \
throw engine::exceptions::AssetFileNotFoundException(assetType, assetFilePath, __FILE__, __LINE__)

#define THROW_ASSET_FILE_IS_A_DIRECTORY(assetType, assetFilePath) \
throw engine::exceptions::AssetPathIsADirectoryException(assetType, assetFilePath, __FILE__, __LINE__)

#define THROW_INVALID_ASSET_FILE_EXTENSION(assetType, assetFilePath) \
throw engine::exceptions::InvalidAssetFileExtension(assetType, assetFilePath, __FILE__, __LINE__)
} // namespace engine::exceptions
