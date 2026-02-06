#include <stdio.h>

struct ADIHeader {
    char magic[3];
    int width;
    int height;
    unsigned char channels;
};

int main(void) {
    int width = 2;
    int height = 2;
    unsigned char channels = 3;

    unsigned char image[12] = {
        255, 242, 222,
        255, 242, 244,
        255, 200, 242,
        244, 222, 244
    };

    struct ADIHeader header;
    header.magic[0] = 'A';
    header.magic[1] = 'D';
    header.magic[2] = 'I';
    header.width = width;
    header.height = height;
    header.channels = channels;


    //file writing
    FILE *fptr=fopen("test.adi","wb");
    if (fptr==NULL){
        return 1;}
    fwrite(&header,sizeof(header),1,fptr);
    fwrite(image,1,(width * height) * channels,fptr);
    fclose(fptr);


    

    return 0;
}

