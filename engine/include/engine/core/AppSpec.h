#pragma once

#include  <string>

namespace engine::core
{

struct AppSpec
{
    std::string windowTitle = "Raylib";
    int width = 640;
    int height = 480;
};

} // namespace engine::core