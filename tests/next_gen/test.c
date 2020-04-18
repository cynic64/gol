#include "../../grid.h"
#include "../../view.h"
#include "../../save.h"

int main() {
    FILE *fp = fopen("saved.gol", "r");

    if (fp == NULL) {
        printf("Could not load saved.gol\n");
        exit(1);
    }

    Grid grid;
    if (load_grid(&grid, fp) != 0) {
        printf("Could not load grid\n");
        exit(1);
    }

    for (int i = 0; i < 50; i++) {
        printf("Generation %d:\n", i);
        print_grid(&grid);
        printf("\n");
        grid_gen(&grid);
        grid_swap(&grid);
    }
}
