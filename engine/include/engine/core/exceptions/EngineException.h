#pragma once
#include <exception>
#include <string>
#include <utility>
#include <spdlog/spdlog.h>

namespace engine::exceptions
{

class EngineException : public std::exception
{
public:
    EngineException(const std::string_view system, std::string message, const char* file = "", const int line = 0)
        : m_message(std::move(message)), m_file(file), m_line(line)
    {

        std::ostringstream messageStream;
        messageStream << "[" << system <<" Error] " << m_message;

        if (file && file[0] != '\0')
            messageStream << " (File: " << file << ", Line: " << line << ")";

        m_message = messageStream.str();
    }

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }

protected:
    std::string m_message;
    std::string m_file;
    int m_line;
};

// Macro to make throwing exceptions easier with automatic file/line info
#define THROW_ENGINE_EXCEPTION(system, message) throw EngineException(system, message, __FILE__, __LINE__)

} // namespace engine::core