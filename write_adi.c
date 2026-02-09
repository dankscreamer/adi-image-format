#include <stdio.h>
#include "adi.h"



int write_adi(const char *filename,
              struct ADIHeader *header,
              unsigned char *pixels)
{
    FILE *fptr = fopen(filename, "wb");
    if (fptr == NULL) {
        return 1;
    }

    /* Write header */
    if (fwrite(header, sizeof(*header), 1, fptr) != 1) {
        fclose(fptr);
        return 1;
    }

    /* Compute pixel byte count */
    size_t pixel_bytes =
    (size_t)(*header).width *
    (size_t)(*header).height *
    (size_t)(*header).channels;
     /* Write pixel data */
    if (fwrite(pixels, 1, pixel_bytes, fptr) != pixel_bytes)
{
        fclose(fptr);
        return 1;
    }

    fclose(fptr);
    return 0;
}



