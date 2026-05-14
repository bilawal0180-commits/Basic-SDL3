#include <SDL3/SDL.h>

SDL_Window* Window = nullptr;
SDL_Renderer* Renderer = nullptr;

bool init(const char*, int, int);
void cleanup();

float getDelta();
void handleInput(bool&);
void movement(SDL_FRect&, const bool*, const float, float);
void render(SDL_FRect&);

int main(int argc, char* argv[])
{

  if (!init("Box", 640, 480)) return 1;

  bool running{true};
  const bool* keyboard = SDL_GetKeyboardState(NULL);
  const float speed{1000.0f};
  SDL_FRect rect = {640/2 - 25, 480/2 - 25, 50, 50}; // Spawn at Center

  while (running) {
    float delta = getDelta();
    handleInput(running);
    movement(rect, keyboard, speed, delta);
    render(rect);
  }

  cleanup();
  return 0;
}

bool init(const char* title, int w, int h)
{
  SDL_Init(SDL_INIT_VIDEO);
  Window = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);
  Renderer = SDL_CreateRenderer(Window, NULL);
  SDL_SetRenderVSync(Renderer, 1);
  return Window && Renderer;
}
void cleanup()
{
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

float getDelta()
{
  static Uint64 lastTime = SDL_GetTicks();
  Uint64 curTime = SDL_GetTicks();
  float delta = (curTime - lastTime) / 1000.0f;
  lastTime = curTime;
  return delta;
}
void handleInput(bool& running)
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) 
    if (e.type == SDL_EVENT_QUIT) running = false;
}
void movement(SDL_FRect& rect, const bool* keyboard, const float speed, float delta)
{
  if (keyboard[SDL_SCANCODE_RIGHT]) rect.x += speed * delta;
  if (keyboard[SDL_SCANCODE_LEFT])  rect.x -= speed * delta;
  if (keyboard[SDL_SCANCODE_UP])    rect.y -= speed * delta;
  if (keyboard[SDL_SCANCODE_DOWN])  rect.y += speed * delta;

}
void render(SDL_FRect& rect)
{
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
  SDL_RenderClear(Renderer);

  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(Renderer, &rect);
  
  SDL_RenderPresent(Renderer);
}

