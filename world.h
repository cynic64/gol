#include <string.h>

#include "chunk.h"

typedef struct World {
    Chunk **chunks;
    // chunk count
    int ccount;
    // chunk capacity (how many chunks there is space allocated for)
    int ccap;
    int cwidth;
    int cheight;
} World;

void world_add(World *world, int cx, int cy);

World world_new(int cwidth, int cheight) {
    World world;
    world.ccount = 0;
    world.cwidth = cwidth;
    world.cheight = cheight;
    world.ccap = 0;

    world_add(&world, 0, 0);

    return world;
}

void world_add(World *world, int cx, int cy) {
    // if there is already a chunk at the requested chunk coordinates, does
    // nothing

    // first scan through all existing chunks to see whether it already exists
    for (int i = 0; i < world->ccount; i++) {
        if (world->chunks[i]->cx == cx && world->chunks[i]->cy == cy) return;
    }

    // create the new chunk
    Chunk *chunk = malloc(sizeof(Chunk));
    chunk_new(chunk, world->cwidth, world->cheight, cx, cy);

    // allocate more space if necessary for a pointer to the chunk
    if (world->ccap == 0) {
        size_t space = sizeof(Chunk *);
        world->chunks = malloc(space);
        world->ccap = 1;
    } if (world->ccap == world->ccount) {
        // double the previous capacity
        size_t space = sizeof(Chunk *) * world->ccap;
        Chunk **ptr = malloc(space * 2);

        // copy old pointers in
        memcpy(ptr, world->chunks, space);

        world->chunks = ptr;
        world->ccap *= 2;
    }

    world->chunks[world->ccount] = chunk;
    world->ccount += 1;

    // scan through existing chunks and potentially set the added chunk as a
    // neighbor
    for (int i = 0; i < world->ccount; i++) {
        Chunk *c = world->chunks[i];

        // check if we added N
        if (chunk->cx == c->cx && chunk->cy == c->cy - 1) {
            c->n = chunk->ctr;
            chunk->s = c->ctr;
        // NE
        } else if (chunk->cx == c->cx + 1 && chunk->cy == c->cy - 1) {
            c->ne = chunk->ctr;
            chunk->sw = c->ctr;
        // E
        } else if (chunk->cx == c->cx + 1 && chunk->cy == c->cy) {
            c->e = chunk->ctr;
            chunk->w = c->ctr;
        // SE
        } else if (chunk->cx == c->cx + 1 && chunk->cy == c->cy + 1) {
            c->se = chunk->ctr;
            chunk->nw = c->ctr;
        // S
        } else if (chunk->cx == c->cx && chunk->cy == c->cy + 1) {
            c->s = chunk->ctr;
            chunk->n = c->ctr;
        // SW
        } else if (chunk->cx == c->cx - 1 && chunk->cy == c->cy + 1) {
            c->sw = chunk->ctr;
            chunk->ne = c->ctr;
        // W
        } else if (chunk->cx == c->cx - 1 && chunk->cy == c->cy) {
            c->w = chunk->ctr;
            chunk->e = c->ctr;
        // NW
        } else if (chunk->cx == c->cx - 1 && chunk->cy == c->cy - 1) {
            c->nw = chunk->ctr;
            chunk->se = c->ctr;
        }
    }
}
