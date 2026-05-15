#include <SDL3/SDL.h>
#include "include/Game/gameLoop.h"

class MyGame : public gameLoop
{
  public:
    void mainLoop() override {
      return;
    }
};

int main(int argc, char* argv[])
{
  MyGame game;
  

  return 0;
}