#ifdef NXDK
#include <hal/xbox.h>
#endif

#include "doubleList.h"
#include "outputLine.h"
#include "navigateMenu.h"
#include "subsystems.h"

#include <threads.h>

#ifdef NXDK
void _exit() { }
#endif

int main(void) {
  int init = init_systems();
  if (init == 0) {
    thrd_t thr;
    thrd_create(&thr, menuLoop, NULL);

    thrd_join(thr, NULL);
  }
  shutdown_systems(init);
  return init;
}
