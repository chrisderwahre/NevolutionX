#include "vector.hpp"
#include "findXBE.h"
#include "gameMenuItem.h"
#include "menuItem.h"
//#include "navigateMenu.h"
#include "outputLine.h"
#include "subsystems.h"

#include <threads.h>

#ifdef NXDK
extern "C" void _exit(int rc) {}

void * __cdecl operator new(unsigned int size) { return malloc(size); }
void __cdecl operator delete(void* itm) { free(itm); }
#endif

int main(void) {
  int init = init_systems();
  vector<menuItem*> mainMenu;
  vector<gameMenuItem*> gamesList;
  mainMenu.push_back(new menuItem("Games"));
  mainMenu.push_back(new menuItem("Applications"));
  mainMenu.push_back(new menuItem("Launch DVD"));
  mainMenu.push_back(new menuItem("Settings"));
  for (int i = 0; i < mainMenu.size(); ++i) {
    menuItem* t = mainMenu.at(i);
    outputLine("%s\n", t->getLabel());
  }
  thrd_t thr;
  if (init == 0) {
    thrd_create(&thr, findXBE, &gamesList);
    thrd_join(thr, nullptr);
    if (gamesList.empty()) {
      gamesList.push_back(new gameMenuItem("Empty", ""));
    }
    for (int i = 0; i < gamesList.size(); ++i) {
      gameMenuItem* t = gamesList.at(i);
      outputLine("%s, %s\n", t->getLabel(), t->getXBEPath());
    }
  }
  gamesList.clear();
  shutdown_systems(init);
  return init;
}
