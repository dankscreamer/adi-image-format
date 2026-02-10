#include <stdio.h>
#include <stdlib.h>

#include "adi.h"

/* stb_image implementation */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s <input_image> <output.adi>\n", argv[0]);
        return 1;
    }

    const char *input_image = argv[1];
    const char *output_adi  = argv[2];

    int width, height, channels;

    /* Step 1: Decode image */
   unsigned char *pixels =
        stbi_load(input_image, &width, &height, &channels, 3);


    if (pixels == NULL) {
        printf("Error: Failed to load image %s\n", input_image);
        return 1;
    }

    /* Step 2: Validate channels */
    if (channels != 1 && channels != 3) {
        printf("Error: Unsupported channel count: %d\n", channels);
        stbi_image_free(pixels);
        return 1;
    }

    /* Step 3: Build ADI header */
    struct ADIHeader header;
    header.magic[0] = 'A';
    header.magic[1] = 'D';
    header.magic[2] = 'I';
    header.width    = width;
    header.height   = height;
    header.channels = (unsigned char)channels;

    /* Step 4: Write ADI file */
    if (write_adi(output_adi, &header, pixels) != 0) {
        printf("Error: Failed to write ADI file %s\n", output_adi);
        stbi_image_free(pixels);
        return 1;
    }

    /* Step 5: Cleanup */
    stbi_image_free(pixels);

    printf("Successfully converted %s → %s\n", input_image, output_adi);
    printf("Dimensions: %dx%d, Channels: %d\n",
           width, height, channels);

    return 0;
}

