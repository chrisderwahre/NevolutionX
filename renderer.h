#ifndef RENDERER_H
#define RENDERER_H

#ifdef NXDK
#include <hal/video.h>
#endif

#include <SDL.h>

class Renderer {
public:
  Renderer();
  ~Renderer();

  int init();
  int clear();
  void flip();

  SDL_Renderer* getRenderer() {return renderer;}

  int setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);

  void drawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst);
  void drawTexture(SDL_Texture* tex, SDL_Rect dst);

  SDL_Texture* surfaceToTexture(SDL_Surface* surf);

private:
  SDL_Renderer *renderer;
  SDL_Window *window;
  Uint32 renderFlags;
  Uint32 windowFlags;
#ifndef NXDK
  int SCREEN_HEIGHT;
  int SCREEN_WIDTH;
#endif
};

#endif
