#include <game.h>

game::game() :
    menu(std::make_unique<start_menu>()),
    window_width(800),
    wnidow_height(800),
    font(LoadFont("../resources/BubbleSans-Regular.otf"))
{
    SetTargetFPS(120);
}

void game::start() {
    InitWindow(window_width,wnidow_height,"Game");

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

void game::run() {
    while(1) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}