#pragma once

namespace engine::core
{

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
};

} // namespace engine::core