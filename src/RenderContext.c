//
// Created by rombus on 8/12/21.
//

#include "RenderContext.h"

#include <Configuration.h>


static RenderContext_Settings DEFAULT_RENDER_CONTEXT_SETTINGS = {
    .title = "2DEngine",
    .xPosition = SDL_WINDOWPOS_CENTERED,
    .yPosition = SDL_WINDOWPOS_CENTERED,
    .width = 1280,
    .height = 720,
    .flags = 0
};

RenderContext *
RenderContext_Create(RenderContext_Settings *renderContextSettings) {
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
        renderContextSettings->title,
        renderContextSettings->xPosition,
        renderContextSettings->yPosition,
        renderContextSettings->width,
        renderContextSettings->height,
        renderContextSettings->flags
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

RenderContext *
RenderContext_CreateDefault() {
    return RenderContext_Create(&DEFAULT_RENDER_CONTEXT_SETTINGS);
}

void
RenderContext_Destroy(RenderContext *renderContext) {
    SDL_DestroyWindow(renderContext->window);
    renderContext->window = NULL;
    SDL_DestroyRenderer(renderContext->renderer);
    renderContext->renderer = NULL;

    free(renderContext);
}

// TODO: This needs to be more generalized, but works simply for now
RenderContext_Settings *
RenderContext_Settings_FromConfig(const ConfigurationJSON *configJson) {
    JSON_Object *renderContextConfig = json_object_get_object(configJson, "renderer");

    // If we don't find the window object, just use defaults
    if (renderContextConfig == NULL) return &DEFAULT_RENDER_CONTEXT_SETTINGS;

    // Create our new render context settings
    RenderContext_Settings *renderContextSettings = malloc(sizeof(RenderContext_Settings));
    memcpy(renderContextSettings, &DEFAULT_RENDER_CONTEXT_SETTINGS, sizeof(RenderContext_Settings));
    if (renderContextSettings == NULL) {
        fprintf(stderr, "Failed to allocate RenderContext_Settings");
        return NULL;
    }

    // Only set width and height from the config for now
    const int width = (int) json_object_get_number(renderContextConfig, "width");
    const int height = (int) json_object_get_number(renderContextConfig, "height");
    if(width != 0) {
        renderContextSettings->width = width;
    }
    if(height != 0) {
        renderContextSettings->height = height;
    }

    return renderContextSettings;
}

