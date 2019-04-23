#include "vector.hpp"
#include "findXBE.h"
#include "gameMenuItem.h"
#include "menuItem.h"
#include "outputLine.h"
#include "renderer.h"
#include "subsystems.h"

#include <threads.h>

#ifdef NXDK
extern "C" void _exit(int rc) {}

void * __cdecl operator new(unsigned int size) { return malloc(size); }
void __cdecl operator delete(void* itm) { free(itm); }
#endif

int main(void) {
  int init = init_systems();
  vector<menuItem> mainMenu;
  vector<gameMenuItem> gamesList;
  if (init == 0) {
    // Create the worker thread for populating the games list
    thrd_t thr;
    thrd_create(&thr, findXBE, &gamesList);

    // Create render system
    Renderer r;
    r.init();

    // Populate main menu
    mainMenu.push_back(menuItem("Games"));
    mainMenu.push_back(menuItem("Applications"));
    mainMenu.push_back(menuItem("Launch DVD"));
    mainMenu.push_back(menuItem("Settings"));

    // Navigate menu and render it
    for (int i = 0; i < mainMenu.size(); ++i) {
      menuItem t = mainMenu.at(i);
      outputLine("%s\n", t.getLabel());
    }

    thrd_join(thr, nullptr);
    if (gamesList.empty()) {
      gamesList.push_back(gameMenuItem("Empty", ""));
    }
    for (int i = 0; i < gamesList.size(); ++i) {
      gameMenuItem t = gamesList.at(i);
      outputLine("%s, %s\n", t.getLabel(), t.getXBEPath());
    }
  }
  mainMenu.clear();
  gamesList.clear();
  shutdown_systems(init);
  return init;
}
