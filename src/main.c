#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderContext.h"
#include "ResourceManager.h"

int
main() {
    RenderContext *renderContext = RenderContext_Create();
    if (renderContext == NULL) {
        fprintf(stderr, "Failed to create a RenderContext\n");
        return 1;
    }

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

    // Test vars
    int t = 0;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Handle events
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

        }

        // Update
        t += 1;

        // Clear the screen
        SDL_SetRenderDrawColor(renderContext->renderer, t / 2 , t / 5, t / 100, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderContext->renderer);

        // Draw
        SDL_Color color = {t, t / 2, t * 2, SDL_ALPHA_OPAQUE};
        SDL_Surface *surface = TTF_RenderText_Blended(foundFont, "Shim a sleepy chumbist", color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderContext->renderer, surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect destinationRect = {20, 20, texW, texH};
        SDL_RenderCopy(renderContext->renderer, texture, NULL, &destinationRect);

        // Present
        SDL_RenderPresent(renderContext->renderer);

        // BS for now
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_Delay(1 / 30);
    }

    ResourceManager_Destroy(fontManager);
    RenderContext_Destroy(renderContext);

    SDL_Quit();

    return 0;
}
