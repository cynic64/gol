#include <stdlib.h>
#include <string.h>

int get_dims(FILE *fp, unsigned *width, unsigned *height);

int load_grid(Grid *grid, FILE *fp) {
    unsigned width, height;

    if (get_dims(fp, &width, &height) != 0) return -1;

    fseek(fp, 0, SEEK_SET);

    *grid = grid_new(width, height);

    for (unsigned y = 0; y < grid->height; y++) {
        for (unsigned x = 0; x < grid->width; x++) {
            int result = fgetc(fp);

            if (result == EOF) return -1;

            if ((char) result == '#') grid_set(grid, x, y, 1);
            else if ((char) result == '.') grid_set(grid, x, y, 0);

            else return -1;
        }
        if (fgetc(fp) != '\n') return -1;
    }

    return 0;
}

int save_grid(Grid *grid, FILE *fp) {
    for (unsigned y = 0; y < grid->height; y++) {
        for (unsigned x = 0; x < grid->width; x++) {
            char c = grid_get(grid, x, y) ? '#' : '.';

            // make sure we actually wrote the character
            if (fputc(c, fp) != c) return -1;
        }

        if (fputc('\n', fp) != '\n') return -1;
    }

    return 0;
}

int get_dims(FILE *fp, unsigned *width, unsigned *height) {
    int buf_size = 1024;
    char *buf = malloc(buf_size);

    *width = 0;
    *height = 0;
    for (;;) {
        if (fgets(buf, buf_size, fp) == NULL) break;

        // either find the width or make sure it matches the existing width
        if (*width == 0) *width = strlen(buf) - 1;
        else if (strlen(buf) != *width + 1) return -1;

        (*height)++;
    }

    free(buf);

    return 0;
}
