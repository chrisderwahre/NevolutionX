#include "menuItemList.h"

/*
 *
 * MENU ITEM
 *
 */

menuItem::menuItem(char* text = nullptr,
                   menuItem* prev = nullptr,
                   menuItem* next = nullptr) : label(text),
  texture(nullptr), height(0), width(0),
  next(next), prev(prev) {}

const char* menuItem::getLabel() {
  return label;
}

void menuItem::setLabel(char* text) {
  label = text;
}

SDL_Texture* menuItem::getTexture() {
  return texture;
}

void menuItem::setTexture(SDL_Texture* tex) {
  texture = tex;
}

SDL_Rect menuItem::getSize() {
  return SDL_Rect(0,0,height,width);
}

int menuItem::getHeight() {
  return height;
}

int menuItem::getWidth() {
  return width;
}

void menuItem::setHeight(int h) {
  height = h;
}

void menuItem::setWidth(int w) {
  width = w;
}


/*
 *
 * MENU ITEM LIST
 *
 */

menuItemList::menuItemList() {
  head = nullptr;
  tail = nullptr;
  font = nullptr;
  length = 0;
}

menuItemList::menuItemList(TTF_Font* font) : menuItemList(), font(font) {
}

menuItemList::~menuItemList() {
  if (!isEmpty()) {
    empty();
  }
  if (font != nullptr) {
    TTF_CloseFont(font);
  }
}

void menuItemList::setFont(TTF_Font *font) {
  if (this->font != nullptr) {
    TTF_CloseFont(this->font);
  }
  this->font = font;
}

void menuItemList::push(menuItem *item) {
  item->next = head;
  item->tail = NULL;
  if (head == NULL) {
    tail = item;
  }
  head = item;
  ++length;
}

void menuItemList::push(char *item) {
  menuItem *tmp = new menuItem(item);
  push(tmp);
}

void menuItemList::append(menuItem *item) {
  item->next = NULL;
  if (head == NULL) {
    push(item);
  } else {
    tail->next = item;
    item->prev = tail;
  }
  tail = item;
  ++length;
}

void menuItemList::append(char *item) {
  menuItem *tmp = new menuItem(item);
  append(tmp);
}

menuItem menuItemList::pop() {
  if (head == nullptr) {
    return nullptr;
  }
  menuItem *ret = head;
  head = ret->next;
  head->prev = nullptr;
  --length;
  return ret;
}

bool menuItemList::isEmpty() {
  return head == NULL;
}

int menuItemList::length() {
  return length;
}

menuItem* menuItemList::find(int key) {
  if (length <= key) {
    return NULL;
  }
  menuItem *ret = head;
  for(int i = 0; i < key; ++i) {
    ret = ret->next;
  }
  return ret;
}

menuItem* menuItemList::remove(int key) {
  if (length <= key) {
    return NULL;
  }
  menuItem *ret = find(key);
  ret->prev->next = ret->next;
  ret->next->prev = ret->prev;
  return ret;
}

void menuItemList::helper_genTexture(SDL_Renderer *renderer, menuItem *itm,
                                     SDL_Color col) {
  if (itm->getTexture != nullptr) {
    SDL_DestroyTexture(itm->getTexture);
  }
  SDL_Surface *surf = TTF_RenderText_Blended(font, itm->getLabel, col);
  if (surf == nullptr) {
    outputLine("TTF_Error: %s", TTF_GetError());
    thrd_exit(4);
  }
  itm->setTexture(SDL_CreateTextureFromSurface(renderer, surf));
  if (itm->getTexture == nullptr) {
    outputLine("Texture creation failed: %s", SDL_GetError());
    thrd_exit(5);
  }
  SDL_FreeSurface(surf);
  SDL_Rect sizes;
  SDL_QueryTexture(itm->getTexture, NULL, NULL, &sizes.w, &sizes.h);
  itm->setWidth(sizes.w);
  itm->setHeight(sizes.h);
}

void menuItemList::generateTextures(SDL_Renderer *renderer, int selected) {
  int i = 0;
  SDL_Color colorSelected = {0xFF, 0x7F, 0xFF, 0xFF};
  SDL_Color colorPassive = {0x7F, 0xFF, 0xFF, 0xFF};
  SDL_Color color;
//  while (tmp != NULL) {
  for (menuItem *itm = head; itm != nullptr; itm = itm->next) {
    if (i != selected) {
      color = colorPassive;
    } else {
      color = colorSelected;
    }
    helper_genTexture(renderer, itm, color);
    ++i;
  }
}

void menuItemList::updateTexture(SDL_Renderer *renderer, int key,
                                 SDL_Color col = {0x7F, 0xFF, 0xFF, 0xFF}) {
  menuItem *tmp = mil_find(key);
  SDL_Color color = {0x7F, 0xFF, 0xFF, 0xFF};
  helper_genTexture(renderer, tmp, color);
}

void menuItemList::updateTwoTextures(SDL_Renderer *renderer,
                                                    int passive, int selected) {
  SDL_Color colorSelected = {0xFF, 0x7F, 0xFF, 0xFF};
  SDL_Color colorPassive = {0x7F, 0xFF, 0xFF, 0xFF};
  menuItem *tmp = find(passive);
  if (tmp != nullptr) {
    helper_genTexture(renderer, tmp, colorPassive);
  }
  tmp = find(selected);
  if (tmp != nullptr) {
    helper_genTexture(renderer, tmp, colorSelected);
  }
}

void menuItemList::mil_drawMenuItems(SDL_Renderer *renderer, menuItemList *mil) {
  SDL_Rect position = {20, 20, 0, 0};
  int renderResult;

  menuItem *tmp = mil->head;
  
  SDL_RenderClear(renderer);
  while (tmp != NULL) {
    position.h = tmp->height;
    position.w = tmp->width;
    renderResult = SDL_RenderCopy(renderer, tmp->texture, NULL, &position);
    if (renderResult != 0) {
      outputLine("menuItem RenderCopy failed: %s", SDL_GetError());
      thrd_exit(3);
    }
    position.y += tmp->height;
    tmp = tmp->next;
  }
}

void menuItemList::empty() {
  menuItem *tmp = nullptr;
  while (head != nullptr) {
    tmp = mil_pop(mil);
    delete(tmp);
  }
}
