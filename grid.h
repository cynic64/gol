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
    // will not set the padding
    if (x != 0 && x != grid->width - 1 && y != 0 && y != grid->height - 1)
        grid->state[y * grid->width + x] = val;
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

Grid grid_new(unsigned width, unsigned height) {
    Grid grid;
    grid.state = malloc(width * height);
    grid.next_state = malloc(width * height);
    grid.width = width;
    grid.height = height;

    return grid;
}
