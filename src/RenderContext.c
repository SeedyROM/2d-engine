//
// Created by rombus on 8/12/21.
//

#include "RenderContext.h"

RenderContext *RenderContext_Create() {
    RenderContext *renderContext = malloc(sizeof(RenderContext));
    renderContext->window = NULL;
    renderContext->renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        return NULL;
    }

    renderContext->window = SDL_CreateWindow(
        "2DEngine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        900,
        500,
        0
    );
    if(renderContext->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return NULL;
    }

    renderContext->renderer = SDL_CreateRenderer(renderContext->window, -1, SDL_RENDERER_ACCELERATED);
    if(renderContext->renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return NULL;
    }

    return renderContext;
}

void RenderContext_Destroy(RenderContext *renderContext) {
    SDL_DestroyWindow(renderContext->window);
    renderContext->window = NULL;
    SDL_DestroyRenderer(renderContext->renderer);
    renderContext->renderer = NULL;

    free(renderContext);
}
