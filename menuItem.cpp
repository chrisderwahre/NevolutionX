#include "menuItem.h"

menuItem::~menuItem() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
}

const char* menuItem::getLabel() {
  return label;
}

void menuItem::setLabel(char* text) {
  label = (char*)realloc(label, strlen(text) * sizeof(char));
  strcpy(label, text);
}

SDL_Texture* menuItem::getTexture() {
  return texture;
}

void menuItem::setTexture(SDL_Texture* t) {
  texture = t;
}
