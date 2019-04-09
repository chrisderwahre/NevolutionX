#ifdef NXDK
#include <hal/xbox.h>
#endif

#include "doubleList.hpp"
#include "gameMenuItem.h"
//#include "navigateMenu.h"
#include "outputLine.h"
#include "subsystems.h"

#include <threads.h>

#ifdef NXDK
void _exit() { }
#endif

int main(void) {
  int init = init_systems();
  doubleList<gameMenuItem*> gamesList;
  gamesList.append(new gameMenuItem("asdasd", "osdosd"));
  if (init == 0) {
/*    thrd_t thr;
    thrd_create(&thr, menuLoop, NULL);
    thrd_join(thr, NULL);*/
    gameMenuItem* t = gamesList.pop();
    outputLine("%s, %s", t->getLabel(), t->getXBEPath());
  }
  shutdown_systems(init);
  return init;
}
