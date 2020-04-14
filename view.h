#include <stdio.h>

void print_grid(Grid *grid, FILE *stream) {
    printf("Grid (%u x %u):\n", grid->width, grid->height);

    for (unsigned y = 0; y < grid->height; y++) {
        for (unsigned x = 0; x < grid->height; x++) {
            putc(grid_get(grid, x, y) ? '#' : '.', stream);
            putc(' ', stream);
        }
        putc('\n', stream);
    }
}
