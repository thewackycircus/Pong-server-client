#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Text.h"
#include "Entity.h"
#include "AssetManager.h"

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
        /*SDL_Rect player1 = { 0, 0, 20, 80 };
        SDL_Rect player2 = { 580, 0, 20, 80 };
        SDL_Rect ball = { 0, 0, 20, 20 };*/

        SDL_Texture* player1Texture;
        SDL_Texture* player2Texture;
        SDL_Texture* ballTexture;

        Entity player1 = Entity(0, 0, 20, 80);
        Entity player2 = Entity(580, 0, 20, 80);
        Entity ball = Entity(0, 0, 20, 20);

        Mix_Chunk* sound;

        AssetManager assetManager = AssetManager();

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void init(SDL_Renderer* renderer);
        SDL_Texture* createTextureFromImg(SDL_Renderer* renderer, std::string img);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);  

        void init_audio();
        void play_sound();
        void destroy();
};

#endif