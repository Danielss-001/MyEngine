#include "engine/platform/Window.hpp"

Window::~Window() {
  if (_window != nullptr) {
    SDL_DestroyWindow(_window);
  }

  if (_sdlInitialized) {
    SDL_Quit();
  }
}

bool Window::Create(const char *title, int width, int height) {
  if (_window != nullptr || _sdlInitialized) {
    return false;
  }

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return false;
  }

  _sdlInitialized = true;

  _window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);

  if (_window == nullptr) {
    return false;
  }

  _running = true;
  return true;
}

bool Window::HandleEvent(const SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    RequestClose();
    return true;

  case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
    if (_window != nullptr &&
        event.window.windowID == SDL_GetWindowID(_window)) {

      RequestClose();
      return true;
    }
    return false;

  default:
    return false;
  }
}

void Window::RequestClose() { _running = false; }

bool Window::ShouldClose() const { return !_running; }
