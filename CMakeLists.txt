cmake_minimum_required(VERSION 3.20)

project(MyEngine
  VERSION 0.1
  LANGUAGES CXX

)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# SDL3 is build as part of this project.
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.0
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL3)

add_executable(MyEngine
  src/main.cpp
  src/platform/Window.cpp
)

target_include_directories(MyEngine
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(MyEngine
  PRIVATE
    SDL3::SDL3
)

# Copy SDL3.dll next to the executable on Windows.
if(WIN32)
  add_custom_command(
    TARGET MyEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:SDL3::SDL3-shared>
      $<TARGET_FILE_DIR:MyEngine>
    VERBATIM
  )
endif()

