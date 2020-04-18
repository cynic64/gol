#include <stdio.h>

#include "../../grid.h"
#include "../../view.h"
#include "../../save.h"

#define WIDTH 20;
#define HEIGHT 20;

int main() {
    Grid grid;
    grid_new(&grid, 10, 10);

    grid_set(&grid, 3, 3, 1);
    grid_set(&grid, 3, 4, 1);
    grid_set(&grid, 3, 5, 1);

    printf("Cell at 4, 3 has %d neighbors (it should have 2)\n",
        count_neighbors(&grid, 4, 3));
    printf("Cell at 4, 4 has %d neighbors (it should have 3)\n",
        count_neighbors(&grid, 4, 4));
    printf("Cell at 4, 5 has %d neighbors (it should have 2)\n",
        count_neighbors(&grid, 4, 5));
    printf("Cell at 3, 4 has %d neighbors (it should have 2)\n",
        count_neighbors(&grid, 3, 4));

    return 0;
}
