#include "vector.hpp"
#include "findXBE.h"
#include "font.h"
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
    xbeFinderArg xfa;
    xfa.list = &gamesList;
    xfa.path = const_cast<char*>("C:\\");
    thrd_t thr;
    thrd_create(&thr, findXBE, &xfa);

    // Create render system
    Renderer r;
    r.init();
    r.setDrawColor(0x40, 0x40, 0xE0, 0xFF);
    r.clear();

    // Create font because do it
    Font f("vegur.ttf");

    // Populate main menu
    mainMenu.push_back(menuItem("Games"));
    mainMenu.push_back(menuItem("Applications"));
    mainMenu.push_back(menuItem("Launch DVD"));
    mainMenu.push_back(menuItem("Settings"));

    int ret = f.createTextures(mainMenu, &r);
    if (ret != mainMenu.size()) {
      outputLine("Shit went south");
    }
    r.drawTexture(r.compileList(mainMenu), 0, 0);

    // Navigate menu and render it
    for (size_t i = 0; i < mainMenu.size(); ++i) {
      menuItem t = mainMenu[i];
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
