#include <stdlib.h>
#include <stdio.h>

#include "../../grid.h"
#include "../../view.h"
#include "../../save.h"

#define WIDTH 40
#define HEIGHT 30

int main() {
    Grid grid;
    grid_new(&grid, WIDTH, HEIGHT);

    srand(0);

    for (unsigned y = 0; y < HEIGHT; y++) {
        for (unsigned x = 0; x < WIDTH; x++) {
            grid_set(&grid, x, y, rand() % 2);
        }
    }

    FILE *fp = fopen("saved.gol", "w");
    if (save_grid(&grid, fp) != 0) {
        printf("Error saving grid\n");
        exit(1);
    }

    if (fclose(fp) != 0) {
        printf("Error closing saved.gol\n");
        exit(1);
    }

    fp = fopen("saved.gol", "r");
    char *buf = malloc(1024);
    size_t count;
    while ((count = fread(buf, 1, 1024, fp)) == 1024) {
        fwrite(buf, 1, 1024, stdout);
    }
    fwrite(buf, 1, count, stdout);

    if (fclose(fp) != 0) {
        printf("Error closing saved.gol\n");
        exit(1);
    }

    return 0;
}
