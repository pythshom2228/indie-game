#include <game.hpp>



Game::Game() :
    menu(std::make_unique<StartMenu>()),
    window_width(800),
    window_height(800)
{
    SetTargetFPS(120);
}

void Game::start() {
    InitWindow(window_width,window_height,"Game");

    bool isRunning = false;
    while(!WindowShouldClose()) {
        
        if(!isRunning) {
            menu->handleInput();
            menu->renderMenu();
        }

        this->run();

    }

    CloseWindow();
}

void Game::run() {
    while(1) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}