#ifndef MENUITEMLIST_H
#define MENUITEMLIST_H

#include "outputLine.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <threads.h>

class menuItem {
private:
  char* label;
  SDL_Texture* texture;
  int height, width;
public:
  menuItem* next;
  menuItem* prev;

  menuItem(char* text, menuItem* prev, menuItem* next);

  const char* getLabel();
  void setLabel(char* text);
  SDL_Texture* getTexture();
  void setTexture(SDL_Texture* tex);
  SDL_Rect getSize();
  int getHeight();
  void setHeight(int h);
  int getWidth();
  void setWidth(int w);
}

class menuItemList {
private:
  menuItem* head;
  menuItem* tail;
  TTF_Font* font;
  int length;
public:
  menuItemList();
  menuItemList(TTF_Font* font);

  ~menuItemList();
  void empty();

  menuItem* begin();
  menuItem* end();

  void setFont(TTF_Font* font);

  void push(menuItem* item);
  void push(char* item);
  void append(menuItem* item);
  void append(char* item);

  menuItem* pop();

  bool isEmpty();
  int length();

  menuItem* find(int key);
  menuItem* remove(int key);

  void generateTextures(SDL_Renderer* renderer, int selected);
  void updateTexture(SDL_Renderer* renderer, int key);
  void updateTwoTextures(SDL_Renderer* renderer, int passive, int selected);
}

#endif
