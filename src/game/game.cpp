#include "game.hpp"

Game::Game() {}

bool Game::init() { return !(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0); }

void Game::start() {}

void Game::stop() { SDL_Quit(); }
