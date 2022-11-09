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

void MyGame::init(SDL_Renderer* renderer) {
    SDL_Surface* redPaddleSurface = IMG_Load("redPaddle.png");
    SDL_Surface* bluePaddleSurface = IMG_Load("bluePaddle.png");
    SDL_Surface* puckSurface = IMG_Load("puck.png");

    SDL_Surface* surfaces[] = { redPaddleSurface, bluePaddleSurface, puckSurface };

    MyGame::checkSurfaces(surfaces);

}

bool MyGame::checkSurfaces(SDL_Surface* surfaces[]) {
    bool status = true;

    for (SDL_Surface i : surfaces) {

    }

    return status;
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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_RenderDrawRect(renderer, &ball);

    SDL_Color white = { 255, 255, 255 };

    Text player1ScoreText = Text();
    Text player2ScoreText = Text();

    player1ScoreText.renderText(renderer,50, 50, std::to_string(game_data.player1Score), white);
    player2ScoreText.renderText(renderer, 750, 50, std::to_string(game_data.player2Score), white);
}