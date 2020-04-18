#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../../grid.h"
#include "../../view.h"
#include "../../save.h"

#define WIDTH 2048
#define HEIGHT 2048
#define BENCH_TIME 4.0

void randomize(Grid *grid);
double get_time();

int main() {
    Grid grid;
    grid_new(&grid, WIDTH, HEIGHT);

    randomize(&grid);

    double stime = get_time();

    int i;
    for (i = 0; get_time() - stime < BENCH_TIME; i++) {
        grid_gen(&grid);
    }

    double dur = get_time() - stime;
    printf("%d generations in %lf sec, %d x %d\n",
        i, dur, WIDTH, HEIGHT);
    printf("Average delta: %lf sec\n", dur / (double) i);

    return 0;
}

void randomize(Grid *grid) {
    srand(0);

    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            grid_set(grid, x, y, rand() % 2);
        }
    }
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec + tv.tv_usec / 1000000;
}
