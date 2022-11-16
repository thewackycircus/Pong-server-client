#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    std::cout << "DATA RECEIVED: " << cmd << ", Args: " << args.size() << std::endl;
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

    player1Texture = MyGame::createTextureFromImg(renderer, "assets/images/redPaddle.png");
    player2Texture = MyGame::createTextureFromImg(renderer, "assets/images/bluePaddle.png");
    ballTexture = MyGame::createTextureFromImg(renderer, "assets/images/ball.png");
}

SDL_Texture* MyGame::createTextureFromImg(SDL_Renderer* renderer, std::string img) {
    SDL_Surface* surface = IMG_Load(img.c_str());

    if (surface != nullptr) {
        std::cout << img << " Loaded" << std::endl;
    }
    else {
        std::cout << img << " Not Loaded" << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
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

    // collision detection debugging

    /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_RenderDrawRect(renderer, &ball);*/

    SDL_RenderCopy(renderer, player1Texture, NULL, &player1);
    SDL_RenderCopy(renderer, player2Texture, NULL, &player2);
    SDL_RenderCopy(renderer, ballTexture, NULL, &ball);

    SDL_Color white = { 255, 255, 255 };

    Text player1ScoreText = Text();
    Text player2ScoreText = Text();

    player1ScoreText.renderText(renderer,50, 50, std::to_string(game_data.player1Score), white);
    player2ScoreText.renderText(renderer, 750, 50, std::to_string(game_data.player2Score), white);
}