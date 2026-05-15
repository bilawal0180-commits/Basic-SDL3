#include <SDL3/SDL.h>
#include "include/Game/gameLoop.h"

class MyGame : public gameLoop
{
  public:
    void draw() override { // TO FIX
      SDL_FRect box = {0, 0, 50, 50};
      SDL_RenderFillRect(Renderer, &box);

    }
};

int main(int argc, char* argv[])
{
  MyGame game;
  game.setBG({255, 255, 255, 255});
  game.init("Snake Game", true);

  game.run();

  return 0;
}