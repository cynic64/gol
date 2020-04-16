#include <stdio.h>

void print_grid(Grid *grid) {
    printf("Grid (%u x %u):\n", grid->width, grid->height);

    for (unsigned y = 0; y < grid->height; y++) {
        for (unsigned x = 0; x < grid->width; x++) {
            putchar(grid_get(grid, x, y) ? '#' : '.');
            putchar(' ');
        }
        putchar('\n');
    }
}
