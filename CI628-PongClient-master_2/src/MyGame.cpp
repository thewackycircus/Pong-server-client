#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    std::cout << "DATA RECEIVED: " << cmd << ", Args: " << args.size() << std::endl;
    if (cmd == "INIT_DATA") {
        game_data.player1X = stoi(args.at(0));
        game_data.player2X = stoi(args.at(1));
    } 
    else if (cmd == "GAME_DATA") {
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    } 
    else if (cmd == "SCORES") {
        if (args.size() == 2) {
            game_data.player1Score = stoi(args.at(0));
            game_data.player2Score = stoi(args.at(1));
        }
    }
    else if (strstr(cmd.c_str(), "HIT_WALL_LEFT") || strstr(cmd.c_str(), "HIT_WALL_RIGHT")) {
        Mix_PlayChannel(-1, AssetManager::getSound("ballToWallSound"), 0);
    } 
    else if (strstr(cmd.c_str(), "BALL_HIT_BAT1") || strstr(cmd.c_str(), "BALL_HIT_BAT2") || strstr(cmd.c_str(), "HIT_WALL_UP") || strstr(cmd.c_str(), "HIT_WALL_DOWN")) {
        Mix_PlayChannel(-1, AssetManager::getSound("ballToPaddleSound"), 0);
    }
    else {
        std::cout << "CMD RECEIVED: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::init(SDL_Renderer* renderer) {

    // initialising mixer and adding sounds to asset manager
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return;
    }

    AssetManager::addSound("ballToWallSound", Mix_LoadWAV("assets/sounds/ballToWall.wav"));
    AssetManager::addSound("ballToPaddleSound", Mix_LoadWAV("assets/sounds/ballToPaddle.wav"));

    // creating textures and adding them to asset manager
    player1Texture = MyGame::createTextureFromImg(renderer, "assets/images/redPaddle.png");
    player2Texture = MyGame::createTextureFromImg(renderer, "assets/images/bluePaddle.png");
    ballTexture = MyGame::createTextureFromImg(renderer, "assets/images/ball.png");

    AssetManager::addTexture("player1Texture", player1Texture);
    AssetManager::addTexture("player2Texture", player2Texture);
    AssetManager::addTexture("ballTexture", ballTexture);

    // opening fonts and adding them to asset manager
    font = TTF_OpenFont("assets/fonts/OpenSans.ttf", 48);

    AssetManager::addFont("font", font);
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
            send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
            break;
        case SDLK_SPACE:
            send(event.type == SDL_KEYDOWN ? "SPACE_DOWN" : "SPACE_UP");
    }
}

void MyGame::update() {
    player1.setPosition(game_data.player1X, game_data.player1Y);
    player2.setPosition(game_data.player2X, game_data.player2Y);
    ball.setPosition(game_data.ballX, game_data.ballY);
}

void MyGame::render(SDL_Renderer* renderer) {

    SDL_Color white = { 255, 255, 255 };

    Text player1ScoreText = Text();
    Text player2ScoreText = Text();

    player1ScoreText.renderText(renderer,50, 50, std::to_string(game_data.player1Score), white, AssetManager::getFont("font"));
    player2ScoreText.renderText(renderer, 750, 50, std::to_string(game_data.player2Score), white, AssetManager::getFont("font"));

    player1.renderEntity(renderer, AssetManager::getTexture("player1Texture"));
    player2.renderEntity(renderer, AssetManager::getTexture("player2Texture"));
    ball.renderEntity(renderer, AssetManager::getTexture("ballTexture"));
}