#include <stdbool.h>
#include <stdlib.h>

#include "ui.h"

#define NUM_DRIPS 250
#define PROB_CHANGE 0.95
#define PROB_DIM 0.65
#define PROB_DRIP_SPAWN 0.65

struct Matrix matrix;

struct Drips {
  int x[NUM_DRIPS];
  int y[NUM_DRIPS];
  bool live[NUM_DRIPS];
  bool brigthness[NUM_DRIPS];
};

static struct Drips drips;

/* matrix_init */

void init_drips(void);

void matrix_init(void) {
  // set the matrix all to black
  for (int i = 0; i < MAXX; ++i) {
    for (int j = 0; j < MAXY; ++j) {
      matrix.characters[i][j] = 0;
      matrix.intensities[i][j] = 0;
    }
  }

  init_drips();
}

void init_drips(void) {
  for (int i = 0; i < NUM_DRIPS; ++i) {
    drips.live[i] = false;
  }
}

/* matrix_update */

double rand01(void);
void try_add_drips(void);
void update_drips(void);
void fade_and_change_matrix(void);
char random_printable_character(void);

void matrix_update(void) {
  if (rand01() < PROB_DRIP_SPAWN) {
    try_add_drips();
  }
  update_drips();

  fade_and_change_matrix();
}

double rand01(void) { return (double)rand() / RAND_MAX; }

void try_add_drips(void) {
  for (int i = 0; i < NUM_DRIPS; ++i) {
    if (drips.live[i] == false) {
      drips.live[i] = true;
      // Determine the initial position of the drip and its intensity
      drips.x[i] = rand() % MAXX;
      drips.y[i] = 0;  // rand() % MAXY
      drips.brigthness[i] = rand() % 2;
      return;
    }
  }
}

void update_drips(void) {
  for (int i = 0; i < NUM_DRIPS; ++i) {
    if (drips.live[i] == true) {
      matrix.intensities[drips.x[i]][drips.y[i]] =
          drips.brigthness[i] ? MAX_INTENSITY : MIN_INTENSITY;

      drips.y[i] += 1;
      if (drips.y[i] >= MAXY - 1) {
        drips.live[i] = false;
      }
    }
  }
}

void fade_and_change_matrix(void) {
  for (int i = 0; i < MAXX; ++i) {
    for (int j = 0; j < MAXY; ++j) {
      // randomly change all characters
      if (rand01() < PROB_CHANGE || matrix.characters[i][j] == 0) {
        matrix.characters[i][j] = random_printable_character();
      }

      // randomly dim all cells
      if (rand01() < PROB_DIM) {
        if (matrix.intensities[i][j] > 0) {
          matrix.intensities[i][j] -= 1;
        }
      }
    }
  }
}

char random_printable_character(void) { return 33 + (rand() % 80); }
