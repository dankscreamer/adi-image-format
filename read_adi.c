#include <stdio.h>
#include <stdlib.h>
#include "adi.h"

unsigned char *read_adi(const char *filename,
                        struct ADIHeader *out_header)
{
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        return NULL;
    }

    /* Read header */
    if (fread(out_header, sizeof(*out_header), 1, fptr) != 1) {
        fclose(fptr);
        return NULL;
    }

    /* Validate magic */
    if ((*out_header).magic[0] != 'A' ||
        (*out_header).magic[1] != 'D' ||
        (*out_header).magic[2] != 'I') {
        fclose(fptr);
        return NULL;
    }

    /* Validate dimensions */
    if ((*out_header).width <= 0 ||
        (*out_header).height <= 0 ||
        (((*out_header).channels != 1) &&
         ((*out_header).channels != 3))) {
        fclose(fptr);
        return NULL;
    }

    /* Compute pixel byte count */
    size_t pixel_bytes =
        (size_t)(*out_header).width *
        (size_t)(*out_header).height *
        (size_t)(*out_header).channels;

    unsigned char *pixels = malloc(pixel_bytes);
    if (pixels == NULL) {
        fclose(fptr);
        return NULL;
    }

    /* Read pixel data */
    if (fread(pixels, 1, pixel_bytes, fptr) != pixel_bytes) {
        free(pixels);
        fclose(fptr);
        return NULL;
    }

    fclose(fptr);
    return pixels;
}

