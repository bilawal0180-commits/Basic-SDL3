#include "Game/gameLoop.h"

gameLoop::gameLoop() : w(640), h(480) {}
gameLoop::gameLoop(int width, int height) : w(width), h(height) {}
gameLoop::~gameLoop() { _cleanup(); }

bool gameLoop::_init(const char* title, bool vsync)
{
  SDL_Init(SDL_INIT_VIDEO);
  active = SDL_CreateWindowAndRenderer(title, w, h, SDL_WINDOW_RESIZABLE, &Window, &Renderer);
  if (active && vsync)
    SDL_SetRenderVSync(Renderer, 1);
  
  _ready(); // For User to Override
  
  return active;
}
void gameLoop::_cleanup()
{
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void gameLoop::_run()
{
  while(isActive()) {
    float delta = getDelta();
    _render();
    _process(delta);
    _handleInput();
  }

}

bool gameLoop::isActive() {return active;}
void gameLoop::setActive(bool val) {active = val;}

void gameLoop::setBG(const SDL_Color& color) noexcept { BG = color; }

void gameLoop::_render()
{
  SDL_SetRenderDrawColor(Renderer, BG.r, BG.g, BG.b, BG.a);
  SDL_RenderClear(Renderer);
  
  _draw();  // For User to Override
  
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
void gameLoop::_handleInput()
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) { 
    if (e.type == SDL_EVENT_QUIT) setActive(false);
    if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) SDL_GetWindowSizeInPixels(Window, &w, &h);
  }

  _input(); // For User to Override
}
