
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    int width, height, channels;

    unsigned char *pixels =
        stbi_load(filename, &width, &height, &channels, 0);

    if (pixels == NULL) {
        printf("Failed to load image: %s\n", filename);
        return 1;
    }

    printf("Image loaded successfully\n");
    printf("Width   : %d\n", width);
    printf("Height  : %d\n", height);
    printf("Channels: %d\n", channels);

    stbi_image_free(pixels);
    return 0;
}

