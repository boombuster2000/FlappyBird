#pragma once
#include <exception>
#include <string>

namespace engine::exceptions
{

class EngineException : public std::exception
{
public:
    explicit EngineException(const std::string_view system, const std::string_view message)
        : m_message(message), m_system(system)
    {
        std::ostringstream messageStream;
        messageStream << "[" << system << " Error] - " << m_message;

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

private:
    std::string m_system;
};

} // namespace engine::core