#ifndef GAMELOOP
#define GAMELOOP

#include <SDL3/SDL.h>

class gameLoop
{
  public:
    gameLoop();
    gameLoop(int, int);
    ~gameLoop();
    
    bool _init(const char*, bool);
    void _run();

    bool isActive();
    void setActive(bool);

    void setBG(const SDL_Color&) noexcept;

    virtual void _ready() = 0;
    virtual void _draw() = 0;
    virtual void _process(float delta) = 0;
    virtual void _input() = 0;
    
    float getDelta() noexcept;
  
  protected:
    bool active{};
    int w{}, h{};
    SDL_Color BG{};
    float mouseX, mouseY;

    const bool* _keyboard = SDL_GetKeyboardState(NULL);
    Uint32 _mouse_buttons = SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    
    void _cleanup();
    void _render();
    void _handleInput();
};

#endif