#include <stdlib.h>
#include <iostream>
#include <chrono>
#include "SDL2/SDL.h"
#include "defs.hpp"
#include "init.hpp"
#include "loop.hpp"
#include "board.hpp"

int main(void) {
    snek::Board board(snek::BOARD_HEIGHT, snek::BOARD_WIDTH);
    snek::App *app = new snek::App;
    memset(app, 0, sizeof(snek::App));

    initSDL(app);

    auto start = std::chrono::steady_clock::now();
    std::pair<int, int> direction;

    while (1) {
        snek::prepareScene(app);

        snek::doInput(direction);

        if ((std::chrono::steady_clock::now() - start) >= std::chrono::milliseconds(250)) {
            start = std::chrono::steady_clock::now();
            snek::doInput(direction);
            switch (board.move_snake(direction)) {
                case 0:
                    break;
                case 1:
                    std::cout << "you died!";
                    exit(0);
                    break;
                case 2:
                    if (board.move_snake(std::pair<int, int>(direction.first * -1, direction.second * -1))) {
                        std::cout << "you died!";
                        exit(0);
                    }
                    break;
                default:
                    break;
            }
        }
        
        board.draw_board(app);

        snek::presentScene(app);

        SDL_Delay(16);
    }
    return 0;
}
