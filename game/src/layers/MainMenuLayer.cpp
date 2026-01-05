#include "game/layers/MainMenuLayer.h"

#include "raylib.h"

void MainMenuLayer::OnUpdate()
{
}

void MainMenuLayer::OnRender()
{
    DrawText("Hello World !", 20, 20, 20, BLACK);
}