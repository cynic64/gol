#include <stdio.h>

#include "../../grid.h"
#include "../../view.h"
#include "../../save.h"

int main() {
    FILE *fp = fopen("saved.gol", "r");

    if (fp == NULL) {
        printf("Could not open saved.gol\n");
        exit(1);
    }

    Grid grid;
    if (load_grid(&grid, fp) != 0) {
        printf("Could not load grid\n");
        exit(1);
    }

    printf("Loaded grid:\n");
    print_grid(&grid);

    return 0;
}
