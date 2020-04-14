#include <stdlib.h>

typedef struct _Grid {
    char *state;
    char *next_state;
    unsigned width;
    unsigned height;
} Grid;

char grid_get(Grid *grid, unsigned x, unsigned y) {
    return grid->state[y * grid->width + x];
}

void grid_set(Grid *grid, unsigned x, unsigned y, char val) {
    grid->state[y * grid->width + x] = val;
}

Grid grid_new(unsigned width, unsigned height) {
    Grid grid;
    grid.state = malloc(width * height);
    grid.next_state = malloc(width * height);
    grid.width = width;
    grid.height = height;

    return grid;
}
