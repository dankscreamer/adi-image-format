#include <stdio.h>
#include <stdlib.h>

struct ADIheader {
    char magic[3];
    int width;
    int height;
    unsigned char channels;
};

int main(void) {
    FILE *fptr = fopen("test.adi", "rb");
    if (fptr == NULL) {
        return 1;
    }

    
    struct ADIheader header;
    fread(&header, sizeof(header), 1, fptr);

    
    if (header.magic[0] != 'A' ||
        header.magic[1] != 'D' ||
        header.magic[2] != 'I') {
        fclose(fptr);
        return 1;
    }

    
    int pixel_bytes = header.width * header.height * header.channels;
    unsigned char *pixels = malloc(pixel_bytes);
    if (pixels == NULL) {
        fclose(fptr);
        return 1;
    }

    
    fread(pixels, 1, pixel_bytes, fptr);
    fclose(fptr);

    
    for (int i = 0; i < pixel_bytes; i++) {
        printf("%d ", pixels[i]);
    }
    printf("\n");

    free(pixels);
    return 0;
}

