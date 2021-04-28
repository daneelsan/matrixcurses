#include "ui.h"

#include <curses.h>

static WINDOW *uiwindow = NULL;

static int color_pair_map[MAX_INTENSITY + 1] = {1, 2, 2, 3, 3, 3, 4,
                                                4, 4, 4, 4, 5, 3, 6};

void set_colors(void);

bool init_ui(void) {
  // init curses
  uiwindow = initscr();
  if (uiwindow == NULL) {
    return false;
  }

  start_color();
  if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
    fputs("Error: Your terminal cannot handle this program.\n", stderr);
    return false;
  }

  set_colors();

  return true;
}

void set_colors(void) {
  for (int i = 0; i < 8; ++i) {
    // (number of color-pair, foreground color number, background color number)
    init_pair(i + 1, i, COLOR_BLACK);
  }

  // set shades of green
  for (int i = 0; i <= 5; ++i) {
    // Redefines colors: init_color(number of the color, R, G, B)
    // The last three arguments must be a value between 0 and 1000
    init_color(i, 0, i * 200, 0);
  }
  init_color(6, 800, 1000, 800);
}

void show_matrix(void) {
  for (int i = 0; i < MAXX; ++i) {
    for (int j = 0; j < MAXY; ++j) {
      // sets the current color of the given window to the foreground/background
      // combination described by the color_pair number
      color_set(color_pair_map[matrix.intensities[i][j]], NULL);
      mvaddch(j, i, matrix.characters[i][j]);
    }
  }

  refresh();
}

void cleanup_ui(void) {
  delwin(uiwindow);
  endwin();
  refresh();
}
