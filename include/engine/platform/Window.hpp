#pragma once

#include <SDL3/SDL.h>

class Window {
private:
  SDL_Window *_window = nullptr;
  bool _running = false;
  bool _sdlInitialized = false;

public:
  Window() = default;
  ~Window();

  // No copi class Guarda
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool Create(const char *title, int width, int height); // Create window
  bool HandleEvent(const SDL_Event &event);              // Handle event
  void RequestClose();                                   // Running false
  bool ShouldClose() const;                              // possible close
};
