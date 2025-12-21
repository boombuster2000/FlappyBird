#include "engine/core/Application.h"

int main()
{
    const engine::core::AppSpec appSpec;
    engine::core::Application game(appSpec);

    game.Run();
    return 0;
}