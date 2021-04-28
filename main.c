#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "matrix.h"
#include "ui.h"

#define ITERATIONS 300
#define REFRESH_DELAY 50000L

int main(int argc, char *argv[]) {
  if (!init_ui()) {
    return EXIT_FAILURE;
  }

  // not necessary as everything is set to zero
  matrix_init();

  for (int i = 0; i < ITERATIONS; ++i) {
    matrix_update();
    show_matrix();
    usleep(REFRESH_DELAY);
  }

  cleanup_ui();

  return EXIT_SUCCESS;
}
