#include <stdio.h>

#include "../../world.h"

void failing_set(Chunk *chunk, int x, int y);

int main() {
    World world = world_new(16, 16);
    world_add(&world, 1, 0);

    Chunk *chunk0 = world.chunks[0];
    Chunk *chunk1 = world.chunks[1];

    // set some cells in chunk1 (which is east of chunk0)
    chunk_set(chunk1, 0, 7, 1);
    chunk_set(chunk1, 0, 8, 1);
    chunk_set(chunk1, 0, 9, 1);

    // count neighbors in chunk0 (should find the bordering cells in chunk1)
    int count = chunk_ncount(chunk0, 15, 8);
    printf("%d neighbors found (expected 3)\n", count);

    return 0;
}
