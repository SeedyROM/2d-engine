#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>

#include "ResourceManager.h"

int
main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
            "BinchEngine",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    ResourceManager *fontManager = ResourceManager_Create();
    if (fontManager == NULL) {
        fprintf(stderr, "Failed to create font ResourceManager\n");
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("../resources/fonts/ObelixPro.ttf", 30);
    if (font == NULL) {
        fprintf(stderr, "TTF_OpenFont failed: %s\n", TTF_GetError());
        return 1;
    }

    ResourceManager_Add(fontManager, "ObelixPro", (uintptr_t) font);

    TTF_Font *foundFont = (TTF_Font *) ResourceManager_Get(fontManager, "ObelixPro");
    if(foundFont == NULL) {
        fprintf(stderr, "Failed to find resource %s", ResourceManager_GetError(fontManager));
        return 1;
    }
    assert(foundFont == font);

    // Test vars
    int t = 0;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

        }

        // Update
        t += 1;

        SDL_SetRenderDrawColor(renderer, t / 2 , t / 5, t / 100, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Draw
        SDL_Color color = {t, t / 2, t * 2, SDL_ALPHA_OPAQUE};
        SDL_Surface *surface = TTF_RenderText_Blended(foundFont, "Shim a sleepy chumbist", color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = {20, 20, texW, texH};

        SDL_RenderCopy(renderer, texture, NULL, &dstrect);

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        SDL_Delay(1 / 30);
    }

    ResourceManager_Destroy(fontManager);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
