#include <stdio.h>

#include "../../world.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

int main() {
    World world = world_new(CHUNK_WIDTH, CHUNK_HEIGHT);

    Chunk *chunk = world.chunks[0];

    // try to get outside a chunk boundary, should return falses
    char state = chunk_get(chunk, CHUNK_WIDTH, 0);
    printf("Cell get past boundary: %d\n", state);

    // now add a chunk east of the chunk we previously got: now the set
    // shouldn't fail, and the get should succeed (even though they both
    // originate from a chunk outside the location given)
    world_add(&world, 1, 0);
    printf("Added chunk at (1, 0)\n");

    chunk_set(world.chunks[1], 0, 0, 1);

    state = chunk_get(chunk, CHUNK_WIDTH, 0);
    printf("Cell get past boundary: %d\n", state);

    // now try to add the same chunk again: it should recognize that the chunk
    // already exists and should not replace the old one
    world_add(&world, 1, 0);
    state = chunk_get(chunk, CHUNK_WIDTH, 0);
    printf("Cell get that should still be set: %d\n", state);

    return 0;
}
