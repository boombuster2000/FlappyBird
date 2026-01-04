#pragma once
#include "engine/core/exceptions/EngineException.h"

namespace engine::exceptions
{

class AssetNotFoundException : public EngineException
{
public:
    explicit AssetNotFoundException(const std::string_view assetType, const std::string_view assetName)
    : EngineException("AssetManager", std::format("{} '{}' not found.", assetType, assetName)),
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
                              const std::string_view message)
    : EngineException("AssetManager", message),
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
    explicit AssetFileNotFoundException(const std::string_view assetType, const std::string_view assetFilePath)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("Failed to find {} file '{}'.", assetType, assetFilePath))
    {
    }
};

class AssetPathIsADirectoryException : public AssetFileException
{
public:
    explicit AssetPathIsADirectoryException(const std::string_view assetType, const std::string_view assetFilePath)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("{} filepath '{}' is a directory.", assetType, assetFilePath))
    {
    }
};

class InvalidAssetFileExtension : public AssetFileException
{
public:
    explicit InvalidAssetFileExtension(const std::string_view assetType, const std::string_view assetFilePath)
    : AssetFileException(assetType,
        assetFilePath,
        std::format("Unsupported {} file format '{}'.", assetType, std::filesystem::path(assetFilePath).extension().string()))
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
} // namespace engine::exceptions
