#pragma once
#include <exception>
#include <string>

namespace engine::exceptions
{

class EngineException : public std::exception
{
public:
    explicit EngineException(const std::string_view system, const std::string_view message, const std::string_view file, const int line)
        : m_message(message), m_file(file), m_line(line), m_system(system)
    {
        std::ostringstream messageStream;
        messageStream << "[" << system << " Error] " << m_message;

        if (file.length() > 0 && file[0] != '\0')
            messageStream << " (File: " << file << ", Line: " << line << ")";

        m_message = messageStream.str();
    }

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }

    [[nodiscard]] const std::string& GetSystem() const
    {
        return m_system;
    }

protected:
    std::string m_message;
    std::string m_file;
    int m_line;

private:
    std::string m_system;
};

// Macro to make throwing exceptions easier with automatic file/line info
#define THROW_ENGINE_EXCEPTION(system, message) throw EngineException(system, message, __FILE__, __LINE__)

} // namespace engine::core