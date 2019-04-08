#ifndef GAMEMENUITEM_H
#define GAMEMENUITEM_H

#include "menuItemList.h"

class gameMenuItem : public menuItem {
private:
  char* xbePath;
public:
  gameMenuItem(char* text, char* p, menuItem* prev, menuItem* next);
  char* getXBEPath();
  void setXBEPath(char* p);
}

#endif
