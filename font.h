#ifndef FONT_H
#define FONT_H

#include "gameMenuItem.h"
#include "renderer.h"
#include "vector.hpp"

#include <SDL.h>
#include "SDL_ttf.h"

class Font {
private:
  bool textureHelper(menuItem* mI, SDL_Color const& c, SDL_Renderer* r);
  TTF_Font* font;
public:
  Font(const char* path);
  ~Font();

  size_t createTextures(vector<menuItem> &items, Renderer* r);
  size_t createListTexture(vector<gameMenuItem> &items, Renderer* r);
};

#endif
