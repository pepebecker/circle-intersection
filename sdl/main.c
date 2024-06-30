#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include "SDL2/SDL_video.h"
#include <SDL2/SDL2_gfxPrimitives.h>

#include "app.h"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

SDL_Window* window;
SDL_Renderer* renderer;
Color color = {0, 0, 0, 0};

void (*onMouseMoveCallback)(int x, int y) = NULL;

void println(const char* message) {
  printf("%s\n", message);
}

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0" );
  SDL_ShowCursor(SDL_DISABLE);
}

void createWindow(const char* title, int32_t width, int32_t height) {
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void runGameLoop(void (*gameLoop)(float), void (*onQuit)()) {
  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  int mouseX = 0, mouseY = 0;
  SDL_Event event;
  while (1) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        onQuit();
        return;
      }
      if (event.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&mouseX, &mouseY);
        if (onMouseMoveCallback != NULL) {
          onMouseMoveCallback(mouseX, mouseY);
        }
      }
    }

    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    double deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency());

    gameLoop(deltaTime);
    SDL_RenderPresent(renderer);
  }
}

void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  color = (Color){r, g, b, a};
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void clearScreen() {
  SDL_RenderClear(renderer);
}

void drawCircle(int32_t x, int32_t y, int32_t r) {
  aacircleRGBA(renderer, x, y, r, color.r, color.g, color.b, color.a);
}

void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void destroyWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void setOnMouseMove(void (*onMouseMove)(int x, int y)) {
  onMouseMoveCallback = onMouseMove;
}

int main(int argc, char **argv) {
  start();
  return 0;
}
