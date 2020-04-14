#include <stdlib.h>

#include "../../grid.h"
#include "../../view.h"

#define WIDTH 40
#define HEIGHT 40

int main() {
    Grid grid = grid_new(WIDTH, HEIGHT);

    srand(0);
    for (unsigned y = 0; y < HEIGHT; y++) {
        for (unsigned x = 0; x < HEIGHT; x++) {
            grid_set(&grid, x, y, rand() % 2);
        }
    }

    print_grid(&grid, stdout);
}
