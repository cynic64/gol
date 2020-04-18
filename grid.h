#include <stdlib.h>

typedef struct Grid {
    char *state;
    char *next_state;
    unsigned width;
    unsigned height;
} Grid;

char *grid_ptr(Grid *grid, unsigned x, unsigned y) {
    return grid->state + (y * grid->width + x);
}

char grid_get(Grid *grid, unsigned x, unsigned y) {
    return *grid_ptr(grid, x, y);
}

void grid_set(Grid *grid, unsigned x, unsigned y, char val) {
    *grid_ptr(grid, x, y) = val;
}

char count_neighbors(Grid *grid, unsigned x, unsigned y) {
    return grid_get(grid, x - 1, y - 1)
        + grid_get(grid, x - 1, y    )
        + grid_get(grid, x - 1, y + 1)
        + grid_get(grid, x    , y - 1)
        + grid_get(grid, x    , y + 1)
        + grid_get(grid, x + 1, y - 1)
        + grid_get(grid, x + 1, y    )
        + grid_get(grid, x + 1, y + 1);
}

void grid_gen(Grid *grid) {
    for (unsigned y = 1; y < grid->height - 1; y++) {
        for (unsigned x = 1; x < grid->width - 1; x++) {
            char neighbors = count_neighbors(grid, x, y);
            if (grid_get(grid, x, y) == 1) {
                // is alive
                if (neighbors == 2 || neighbors == 3)
                    grid->next_state[y * grid->width + x] = 1;
                else
                    grid->next_state[y * grid->width + x] = 0;
            } else {
                // is dead
                if (neighbors == 3)
                    grid->next_state[y * grid->width + x] = 1;
                else
                    grid->next_state[y * grid->width + x] = 0;
            }
        }
    }

    char *tmp = grid->state;
    grid->state = grid->next_state;
    grid->next_state = tmp;
}

void grid_new(Grid *grid, unsigned width, unsigned height) {
    grid->state = malloc(width * height);
    grid->next_state = malloc(width * height);
    grid->width = width;
    grid->height = height;
}
