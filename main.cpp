#include <iostream>
#include <SDL3/SDL.h>
#include "include/Game/gameLoop.h"

class MyGame : public gameLoop
{
  private:
    SDL_FRect box = {0, 0, 50, 50};

  public:
    void _ready() override {}
    void _draw() override {
      SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
      SDL_RenderFillRect(Renderer, &box);
    }
    void _process(float delta) override {}
    void _input() override {
      if (_keyboard[SDL_SCANCODE_RIGHT])  box.x = w - 50;
      if (_keyboard[SDL_SCANCODE_LEFT])   box.x = 0;
      if (_keyboard[SDL_SCANCODE_UP])     box.y = 0;
      if (_keyboard[SDL_SCANCODE_DOWN])   box.y = h - 50;
    }
};

int main(int argc, char* argv[])
{
  MyGame game;
  game.setBG({0, 0, 0, 255});
  game._init("Snake Game", true);
  game._run();

  return 0;
}