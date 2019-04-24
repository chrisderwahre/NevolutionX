#include "font.h"

Font::Font(const char* path) {
  font = TTF_OpenFont(path, 24);
}

Font::~Font() {
  if (font != nullptr) {
    TTF_CloseFont(font);
  }
}

bool Font::textureHelper(menuItem* mI, SDL_Color const& c, SDL_Renderer* r) {
  if (mI->getTexture() != nullptr) {
    SDL_DestroyTexture(mI->getTexture());
  }
  SDL_Surface *tmpSurf = TTF_RenderText_Blended(font, mI->getLabel(), c);
  if (tmpSurf == nullptr) {
    return false;
  }
  mI->setTexture(SDL_CreateTextureFromSurface(r, tmpSurf));
  if (mI->getTexture() == nullptr) {
    return false;
  }
  SDL_FreeSurface(tmpSurf);
  return true;
}

size_t Font::createTextures(vector<menuItem> &items, Renderer* r) {
  if (r->getRenderer() == nullptr || items.empty()) {
    return 0;
  }
  SDL_Color active = {0x7F, 0x7F, 0xFF, 0xFF};
  SDL_Color passive = {0xFF, 0x7F, 0xFF, 0xFF};

  for (size_t i = 0; i < items.size(); ++i) {
    SDL_Color color = (i == 0 ? active : passive);
    if (!textureHelper(&items[i], color, r->getRenderer())) {
      return i;
    }
  }
  return items.size();
}

size_t Font::createListTexture(vector<gameMenuItem> &items, Renderer* r) {
  return 0;
}
