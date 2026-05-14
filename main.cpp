#include <SDL3/SDL.h>

struct game
{
  int w{}, h{};

  SDL_Window* Window = nullptr;
  SDL_Renderer* Renderer = nullptr;
  
  game();
  game(int, int);

  bool init(const char*);
  void cleanup();
  
  void movement(SDL_FRect&, const bool*, const float, float);
  void render(SDL_FRect&);
  
  void wrapRect(SDL_FRect&);

  float getDelta();
  void handleInput(bool&);

};



int main(int argc, char* argv[])
{

  game game(640, 480);

  if (!game.init("Box")) return 1;

  bool running{true};
  const bool* keyboard = SDL_GetKeyboardState(NULL);
  const float speed{1000.0f};
  SDL_FRect rect = {640/2 - 25, 480/2 - 25, 50, 50}; // Spawn at Center

  while (running) {
    float delta = game.getDelta();
    game.handleInput(running);
    game.movement(rect, keyboard, speed, delta);
    game.render(rect);
  }

  game.cleanup();
  return 0;
}

game::game() : w(0), h(0) {}
game::game(int width, int height) : w(width), h(height) {}

bool game::init(const char* title)
{
  SDL_Init(SDL_INIT_VIDEO);
  Window = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);
  Renderer = SDL_CreateRenderer(Window, NULL);
  SDL_SetRenderVSync(Renderer, 1);
  return Window && Renderer;
}
void game::cleanup()
{
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void game::wrapRect(SDL_FRect& rect)
{
  if (rect.x > w)               rect.x = 0;
  else if (rect.x + rect.w < 0) rect.x = w;
  if (rect.y > h)               rect.y = 0;
  else if (rect.y + rect.h < 0) rect.y = h;

}

void game::movement(SDL_FRect& rect, const bool* keyboard, const float speed, float delta)
{
  
  if (keyboard[SDL_SCANCODE_RIGHT]) rect.x += speed * delta;
  if (keyboard[SDL_SCANCODE_LEFT])  rect.x -= speed * delta;
  if (keyboard[SDL_SCANCODE_UP])    rect.y -= speed * delta;
  if (keyboard[SDL_SCANCODE_DOWN])  rect.y += speed * delta;

  wrapRect(rect);

}
void game::render(SDL_FRect& rect)
{
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
  SDL_RenderClear(Renderer);

  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(Renderer, &rect);
  
  SDL_RenderPresent(Renderer);
}

float game::getDelta()
{
  static Uint64 lastTime = SDL_GetTicks();
  Uint64 curTime = SDL_GetTicks();
  float delta = (curTime - lastTime) / 1000.0f;
  lastTime = curTime;
  return delta;
}
void game::handleInput(bool& running)
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) 
    if (e.type == SDL_EVENT_QUIT) running = false;
    if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) SDL_GetWindowSizeInPixels(Window, &w, &h);
}
