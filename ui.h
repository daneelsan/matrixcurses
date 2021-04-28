#ifndef _UI_H_
#define _UI_H_

#include <stdbool.h>

#define MAXX 160
#define MAXY 50

#define MAX_INTENSITY 13
#define MIN_INTENSITY 2

struct Matrix {
  char characters[MAXX][MAXY];
  int intensities[MAXX][MAXY];
};

// extern - defined in matrix.c
extern struct Matrix matrix;

// prototypes
bool init_ui(void);
void cleanup_ui(void);
void show_matrix(void);

#endif  // _UI_H_
