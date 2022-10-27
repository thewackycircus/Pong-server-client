#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "INIT_DATA") {
        if (args.size() == 2) {
            std::cout << "INIT_DATA," << stoi(args.at(0)) << "," << stoi(args.at(1)) << std::endl;
            game_data.player1X = stoi(args.at(0));
            game_data.player2X = stoi(args.at(1));
        }
    } else if (cmd == "GAME_DATA") {
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    } else if (cmd == "SCORES") {
        if (args.size() == 2) {
            game_data.player1Score = stoi(args.at(0));
            game_data.player2Score = stoi(args.at(1));
        }
    } else {
        std::cout << "CMD RECEIVED: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::init() {
    font = TTF_OpenFont("fonts/OpenSans.ttf", 32);
    if (!font) {
        printf("TTF_INIT: %s\n", TTF_GetError());
        exit(0);
    }
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            break;
        case SDLK_SPACE:
            send(event.type == SDL_KEYDOWN ? "SPACE_DOWN" : "SPACE_UP");
    }
}

void MyGame::update() {
    player1.x = game_data.player1X;
    player1.y = game_data.player1Y;
    player2.x = game_data.player2X;
    player2.y = game_data.player2Y;
    ball.x = game_data.ballX;
    ball.y = game_data.ballY;
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_Color white = { 255, 255, 255 };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_RenderDrawRect(renderer, &ball);

    std::string text = "Player 1: ";
    text += std::to_string(game_data.player1Score);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(message, NULL, NULL, &texW, &texH);
    SDL_Rect messageRect = { 0, 0, texW, texH };

    SDL_RenderCopy(renderer, message, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}