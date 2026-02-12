#include <stdio.h>
#include <stdlib.h>

#include "adi.h"
#include <SDL.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <image.adi>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    struct ADIHeader header;
    unsigned char *pixels = read_adi(filename, &header);

    if (pixels == NULL) {
        printf("Failed to read ADI file\n");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        free(pixels);
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "ADI Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        header.width,
        header.height,
        0
    );

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(pixels);
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        free(pixels);
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STATIC,
        header.width,
        header.height
    );

    if (texture == NULL) {
        printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        free(pixels);
        return 1;
    }

    SDL_UpdateTexture(texture, NULL, pixels, header.width * header.channels);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_Delay(10);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(pixels);

    return 0;
}

