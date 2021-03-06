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

    chunk->n = NULL;
    chunk->ne = NULL;
    chunk->e = NULL;
    chunk->se = NULL;
    chunk->s = NULL;
    chunk->sw = NULL;
    chunk->w = NULL;
    chunk->nw = NULL;
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

char chunk_check_cell(Chunk *chunk, int x, int y) {
    // updates the cell at (x, y) within the central grid. Used to update
    // border cells.

    // returns 1 if the cell was set, 0 otherwise

    int neighbors = chunk_ncount(chunk, x, y);
    char state = grid_get(chunk->ctr, x, y);
    if ((state && neighbors == 2 || neighbors == 3) ||
        (!state && neighbors == 3)) {
        chunk->ctr->next_state[y * chunk->ctr->width + x] = 1;
        return 1;
    } else {
        chunk->ctr->next_state[y * chunk->ctr->width + x] = 0;
        return 0;
    }
}

int chunk_gen(Chunk *chunk) {
    // first calculate the next state for all cells in the center (does not
    // swap buffers yet)
    grid_gen(chunk->ctr);

    // then do borders, and if any become set on and we have some NULL
    // surroundings, return 1 to signal that we want all surrounding chunks to be generated
    int ret = 0;

    // top & bottom
    for (int x = 0; x < chunk->ctr->width; x++) {
        if (chunk_check_cell(chunk, x, 0) || chunk_check_cell(chunk, x, chunk->ctr->height-1))
            ret = -1;
    }

    // left and right
    for (int y = 0; y < chunk->ctr->height; y++) {
        if (chunk_check_cell(chunk, 0, y) || chunk_check_cell(chunk, chunk->ctr->width-1, y))
            ret = -1;
    }

    return ret;
}

void chunk_swap(Chunk *chunk) {
    grid_swap(chunk->ctr);
}
