#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

static struct GameData {
    int player1X = 0;
    int player1Y = 0;
    int player2X = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
    int player1Score = 0;
    int player2Score = 0;
} game_data;

class MyGame {

    private:
        SDL_Rect player1 = { 0, 0, 20, 80 };
        SDL_Rect player2 = { 580, 0, 20, 80 };
        SDL_Rect ball = { 0, 0, 20, 20 };

        TTF_Font* font;

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void init();
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif