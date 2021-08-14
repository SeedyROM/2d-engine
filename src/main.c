#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderContext.h"
#include "ResourceManager.h"

int
main() {
    //
    // Create from defaults
    // RenderContext *renderContext = RenderContext_CreateDefault();
    //

    //
    // Create from a JSON configuration
    //
    static const char *settingsPath = "../config/settings.json";
    RenderContext_Settings *settings = RenderContext_Settings_FromConfig(settingsPath);
    if (settings == NULL) {
        return 1;
    }

    RenderContext *renderContext = RenderContext_Create(settings);
    if (renderContext == NULL) {
        fprintf(stderr, "Failed to create a RenderContext\n");
        return 1;
    }
    //
    // End RenderContext creation
    //

    // Create a font ResourceManager, should this just be its own generic data structure?
    ResourceManager *fontManager = ResourceManager_Create();
    if (fontManager == NULL) {
        fprintf(stderr, "Failed to create font ResourceManager\n");
        return 1;
    }

    // Load a font
    TTF_Font *font = TTF_OpenFont("../resources/fonts/ObelixPro.ttf", 30);
    if (font == NULL) {
        fprintf(stderr, "TTF_OpenFont failed: %s\n", TTF_GetError());
        return 1;
    }
    ResourceManager_Add(fontManager, "ObelixPro", (uintptr_t) font);

    // Retrieve the font from our ResourceManager
    TTF_Font *foundFont = (TTF_Font *) ResourceManager_Get(fontManager, "ObelixPro");
    if(foundFont == NULL) {
        fprintf(stderr, "Failed to find resource %s", ResourceManager_GetError(fontManager));
        return 1;
    }

    // Test vars
    int t = 0;

    //
    // Game loop...
    //
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
