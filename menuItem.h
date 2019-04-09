#ifndef MENUITEM_H
#define MENUITEM_H

class menuItem {
private:
  char* label;
public:
  menuItem(char* text) : label(text) {}
  const char* getLabel();
  void setLabel(char* text);
};
#endif
