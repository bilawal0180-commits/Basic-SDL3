#ifndef GAMELOOP
#define GAMELOOP

#include <SDL3/SDL.h>

class gameLoop
{
  public:
    gameLoop();
    gameLoop(int, int);
    ~gameLoop();
    
    bool init(const char*, bool);
    void run();

    bool isActive();
    void setActive(bool);

    void setBG(const SDL_Color&) noexcept;

    virtual void draw() = 0;
    
    float getDelta() noexcept;
  
  protected:
    bool active{};
    int w{}, h{};
    SDL_Color BG{};
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    
    void cleanup();
    void render();
    void handleInput();
};

#endif