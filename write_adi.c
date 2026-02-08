#include <stdio.h>
#include <stdlib.h>

struct ADIHeader {
    char magic[3];
    int width;
    int height;
    unsigned char channels;
};

unsigned char *read_adi(const char *filename,
                        struct ADIHeader *out_header)
{
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        return NULL;
    }

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

    int pixel_bytes =
        (*out_header).width *
        (*out_header).height *
        (*out_header).channels;

    unsigned char *pixels = malloc(pixel_bytes);
    if (pixels == NULL) {
        fclose(fptr);
        return NULL;
    }

    if (fread(pixels, 1, pixel_bytes, fptr) != pixel_bytes) {
        free(pixels);
        fclose(fptr);
        return NULL;
    }

    fclose(fptr);
    return pixels;
}

int main(void)
{
    struct ADIHeader header;
    unsigned char *pixels = read_adi("test.adi", &header);

    if (pixels == NULL) {
        return 1;
    }

    /* use pixels + header */

    free(pixels);
    return 0;
}

