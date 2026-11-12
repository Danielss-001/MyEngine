#include <SDL3/SDL.h>
#include <iostream>

#include "engine/platform/Window.hpp"

int main() {

  Window window;

  if (!window.Create("MyEngine", 1280, 720)) {
    std::cerr << "Error to create window: " << SDL_GetError() << std::endl;

    return 1;
  }

  while (!window.ShouldClose()) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      window.HandleEvent(event);
    }

    //
    //
    //
    //
    //

    SDL_Delay(16);
  }

  return 0;
}
