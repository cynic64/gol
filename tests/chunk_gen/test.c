#include <stdio.h>
#include <assert.h>

#include "../../chunk.h"
#include "../../save.h"
#include "../../view.h"

int main() {
    // read from file and load
    FILE *fp = fopen("saved.gol", "r");
    assert(fp != NULL);

    Grid grid;
    assert(load_grid(&grid, fp) == 0);

    // create a new chunk and replace the empty grid with the one we loaded
    Chunk chunk;
    chunk_new(&chunk, grid.width, grid.height, 0, 0);
    chunk.ctr = &grid;

    // see how many generations it takes to fail (but don't run more than 128)
    int i;
    for (i = 0; i < 128; i++) {
        if (chunk_gen(&chunk) != 0) break;
        chunk_swap(&chunk);
        print_grid(chunk.ctr);
    }

    assert(i < 128);

    printf("Failed after %d generations\n", i);

    return 0;
}
