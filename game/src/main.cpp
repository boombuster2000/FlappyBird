#include "engine/core/Application.h"
#include "engine/core/ServiceLocator.h"

#include "game/layers/MainMenuLayer.h"

int main()
{
    const engine::core::AppSpec appSpec;
    engine::core::Application game(appSpec);

    // ReSharper disable once CppDFALocalValueEscapesFunction
    // The game's lifetime covers entire program execution so this is safe.
    engine::core::ServiceLocator::SetApp(&game);

    game.QueuePushLayer<MainMenuLayer>();
    game.Run();
    return 0;
}