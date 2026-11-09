#include "SDL3/SDL_init.h"
#include <SDL3/SDL.h>
#include <iostream>

int main() {

  // 1. Initialize subsystem to video SDL3
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Error initialize SDL3: " << SDL_GetError() << "\n";
    return 1;
  }

  // 2. Create Window to engine
  SDL_Window *window =
      SDL_CreateWindow("MyEngine", 1280, 720, SDL_WINDOW_RESIZABLE);

  if (window == nullptr) {
    std::cerr << "Error to create window: " << SDL_GetError() << "\n";

    SDL_Quit();
    return 1;
  }

  // 3. Principal Bucle
  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    SDL_Delay(16);
  }

  // 4. Free resourses
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
