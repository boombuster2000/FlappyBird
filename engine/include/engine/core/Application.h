#pragma once

#include "engine/core/AppSpec.h"

namespace engine::core
{

    class Application
    {
        public:
        explicit Application(const AppSpec& appSpec);
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        static void Run();
    };

} // namespace engine::core
