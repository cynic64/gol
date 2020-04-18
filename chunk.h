#include "grid.h"

typedef struct Chunk {
    Grid *ctr;
    int cx;
    int cy;
    Grid *n;
    Grid *ne;
    Grid *e;
    Grid *se;
    Grid *s;
    Grid *sw;
    Grid *w;
    Grid *nw;
} Chunk;

void chunk_new(Chunk *chunk, int cwidth, int cheight, int cx, int cy) {
    chunk->ctr = malloc(sizeof(Chunk));
    grid_new(chunk->ctr, cwidth, cheight);

    chunk->cx = cx;
    chunk->cy = cy;
}

char *chunk_ptr(Chunk *chunk, int x, int y) {
    // returns a pointer to the requested coordinates, or NULL if they do not
    // exist
    int cw = chunk->ctr->width;
    int ch = chunk->ctr->height;

    // if the requested position is out of bounds and we know of no other grid
    // that could have it, returns false
    if (x >= 0 && x < chunk->ctr->width && y >= 0 && y < chunk->ctr->height)
        return grid_ptr(chunk->ctr,
            (unsigned) x, (unsigned) y);
    // check N
    else if (x >= 0 && x < cw && y < 0 && chunk->n != NULL)
        return grid_ptr(chunk->n,
            (unsigned) x, (unsigned) (y + ch));

    // check NE
    else if (x >= cw && y < 0 && chunk->ne != NULL)
        return grid_ptr(chunk->ne,
            (unsigned) (x - cw), (unsigned) (y + ch));

    // check E
    else if (x >= cw && y >= 0 && y < ch && chunk->e != NULL)
        return grid_ptr(chunk->e,
            (unsigned) (x - cw), (unsigned) y);

    // check SE
    else if (x >= cw && y >= ch && chunk->se != NULL)
        return grid_ptr(chunk->n,
            (unsigned) (x - cw), (unsigned) (y - ch));

    // check S
    else if (x >= 0 && x < cw && y >= ch && chunk->s != NULL)
        return grid_ptr(chunk->s,
            (unsigned) x, (unsigned) (y - ch));

    // check SW
    else if (x < 0 && y > ch && chunk->sw != NULL)
        return grid_ptr(chunk->sw,
            (unsigned) (x + cw), (unsigned) (y - ch));

    // check W
    else if (x < 0 && y >= 0 && y < ch && chunk->w != NULL)
        return grid_ptr(chunk->w,
            (unsigned) (x + cw), (unsigned) y);

    // check NW
    else if (x < 0 && y < 0 && chunk->nw != NULL)
        return grid_ptr(chunk->nw,
            (unsigned) (x + cw), (unsigned) (y + ch));

    return NULL;
}

char chunk_get(Chunk *chunk, int x, int y) {
    char *ptr = chunk_ptr(chunk, x, y);

    if (ptr == NULL) return 0;

    return *ptr;
}

void chunk_set(Chunk *chunk, int x, int y, char val) {
    // will not go across chunk boundaries
    grid_set(chunk->ctr, x, y, val);
}

int chunk_ncount(Chunk *chunk, int x, int y) {
    // counts neighbors at the specified coordinates within a chunk, crossing
    // boundaries if apppropriate.
    return chunk_get(chunk, x - 1, y - 1)
        + chunk_get(chunk, x - 1, y    )
        + chunk_get(chunk, x - 1, y + 1)
        + chunk_get(chunk, x    , y - 1)
        + chunk_get(chunk, x    , y + 1)
        + chunk_get(chunk, x + 1, y - 1)
        + chunk_get(chunk, x + 1, y    )
        + chunk_get(chunk, x + 1, y + 1);
}

int chunk_gen(Chunk *chunk) {
    // first calculate the next state for all cells in the center (does not
    // swap buffers yet)
    grid_gen(chunk->ctr);
}
