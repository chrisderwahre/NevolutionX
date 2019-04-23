#include "renderer.h"

#ifdef NXDK
extern "C" {
const extern int SCREEN_HEIGHT;
const extern int SCREEN_WIDTH;
}
#endif

Renderer::Renderer() {
  window = nullptr;
  renderer = nullptr;
#ifdef NXDK
  windowFlags = SDL_WINDOW_SHOWN;
  renderFlags = 0;
#else
  windowFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE;
  renderFlags = SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED;
  SCREEN_WIDTH = 640;
  SCREEN_HEIGHT = 480;
#endif
}

Renderer::~Renderer() {
  if (renderer != nullptr) {
    SDL_DestroyRenderer(renderer);
  }
  if (window != nullptr) {
    SDL_DestroyWindow(window);
  }
}

int Renderer::init() {
  window = SDL_CreateWindow("NevolutionX",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
  if (window == nullptr) {
    return 1;
  }
  renderer = SDL_CreateRenderer(window, -1, renderFlags);
  if (renderer == nullptr) {
    return 2;
  }
  return 0;
}

int Renderer::clear() {
  return SDL_RenderClear(renderer);
}

void Renderer::flip() {
  SDL_RenderPresent(renderer);
#ifdef NXDK
  XVideoWaitForVBlank();
#endif
}

int Renderer::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::drawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst) {
  SDL_RenderCopy(renderer, tex, &src, &dst);
}

void Renderer::drawTexture(SDL_Texture* tex, SDL_Rect dst) {
  SDL_RenderCopy(renderer, tex, nullptr, &dst);
}

SDL_Texture* Renderer::surfaceToTexture(SDL_Surface* surf) {
  return SDL_CreateTextureFromSurface(renderer, surf);
}
