#include "Game/gameLoop.h"

gameLoop::gameLoop() : w(640), h(480) {}
gameLoop::gameLoop(int width, int height) : w(width), h(height) {}
gameLoop::~gameLoop() { cleanup(); }

bool gameLoop::init(const char* title, bool vsync)
{
  SDL_Init(SDL_INIT_VIDEO);
  active = SDL_CreateWindowAndRenderer(title, w, h, SDL_WINDOW_RESIZABLE, &Window, &Renderer);
  if (vsync)
    SDL_SetRenderVSync(Renderer, 1);
  
  return active;
}
void gameLoop::cleanup()
{
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void gameLoop::run()
{
  while(isActive()) {
    render();
    handleInput();
  }

}

bool gameLoop::isActive() {return active;}
void gameLoop::setActive(bool val) {active = val;}

void gameLoop::setBG(const SDL_Color& color) noexcept { BG = color; }

void gameLoop::render()
{
  SDL_SetRenderDrawColor(Renderer, BG.r, BG.g, BG.b, BG.a);
  SDL_RenderClear(Renderer);
  
  this->draw();  // NOT WORKING?
  
  SDL_RenderPresent(Renderer);
}

float gameLoop::getDelta() noexcept
{
  static Uint64 lastTime = SDL_GetTicks();
  Uint64 curTime = SDL_GetTicks();
  float delta = (curTime - lastTime) / 1000.0f;
  lastTime = curTime;
  return delta;
}
void gameLoop::handleInput()
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) { 
    if (e.type == SDL_EVENT_QUIT) setActive(false);
    if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) SDL_GetWindowSizeInPixels(Window, &w, &h);
  }
}
