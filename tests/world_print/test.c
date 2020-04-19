#include "../../world.h"

// use very small chunks
#define CWIDTH 4
#define CHEIGHT 4

int main() {
    World world = world_new(CWIDTH, CHEIGHT);

    // add chunks all around the central one (which comes by default when the
    // world is created) except southeast (to test printing even when chunks
    // are missing)
    world_add(&world, -1, -1);
    world_add(&world, -1,  0);
    world_add(&world, -1,  1);
    world_add(&world,  0, -1);
    world_add(&world,  0,  1);
    world_add(&world,  1, -1);
    world_add(&world,  1,  0);

    // set cells within each
    // ctr (0, 0)
    grid_set(world.chunks[0]->ctr, 0, 0, 1);
    // nw (-1, -1)
    grid_set(world.chunks[1]->ctr, 0, 1, 1);
    // w (-1, 0)
    grid_set(world.chunks[2]->ctr, 0, 2, 1);
    // sw (-1, 1)
    grid_set(world.chunks[3]->ctr, 0, 3, 1);
    // n (0, -1)
    grid_set(world.chunks[4]->ctr, 1, 0, 1);
    // s (0, 1)
    grid_set(world.chunks[5]->ctr, 1, 1, 1);
    // nw (1, -1)
    grid_set(world.chunks[6]->ctr, 1, 2, 1);
    // e (1, 0)
    grid_set(world.chunks[7]->ctr, 1, 3, 1);

    // print!
    world_print(&world);
}
