#include "engine/core/ServiceLocator.h"

void engine::core::ServiceLocator::SetApp(Application* app)
{
    s_app = app;
}