#include <stdio.h>
#include <stdlib.h>
#include "adi.h"

int main(void)
{
    /* ---- Step 1: Create test image ---- */

    struct ADIHeader header;
    header.magic[0] = 'A';
    header.magic[1] = 'D';
    header.magic[2] = 'I';
    header.width = 2;
    header.height = 2;
    header.channels = 3;

    unsigned char original_pixels[12] = {
        255, 242, 222,
        255, 242, 244,
        255, 200, 242,
        244, 222, 244
    };

    /* ---- Step 2: Write ADI file ---- */

    if (write_adi("test.adi", &header, original_pixels) != 0) {
        printf("ERROR: write_adi failed\n");
        return 1;
    }

    /* ---- Step 3: Read ADI file ---- */

    struct ADIHeader read_header;
    unsigned char *read_pixels = read_adi("test.adi", &read_header);

    if (read_pixels == NULL) {
        printf("ERROR: read_adi failed\n");
        return 1;
    }

    /* ---- Step 4: Validate header ---- */

    if (read_header.width != header.width ||
        read_header.height != header.height ||
        read_header.channels != header.channels) {
        printf("ERROR: header mismatch\n");
        free(read_pixels);
        return 1;
    }

    /* ---- Step 5: Validate pixel data ---- */

    size_t total_bytes =
        (size_t)header.width *
        (size_t)header.height *
        (size_t)header.channels;

    for (size_t i = 0; i < total_bytes; i++) {
        if (original_pixels[i] != read_pixels[i]) {
            printf("ERROR: pixel mismatch at byte %zu\n", i);
            free(read_pixels);
            return 1;
        }
    }

    /* ---- Step 6: Success ---- */

    printf("TEST PASSED: ADI read/write is correct\n");

    free(read_pixels);
    return 0;
}

