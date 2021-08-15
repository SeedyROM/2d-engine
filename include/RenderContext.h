//
// Created by rombus on 8/12/21.
//

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Configuration.h"

typedef struct
RenderContext_Settings {
    const char *title;
    int xPosition;
    int yPosition;
    int width;
    int height;
    int flags;
} RenderContext_Settings;

typedef struct
RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
    RenderContext_Settings *settings;
} RenderContext;

RenderContext *
RenderContext_Create(RenderContext_Settings *);

RenderContext *
RenderContext_CreateDefault();

void
RenderContext_Destroy(RenderContext *);

RenderContext_Settings *
RenderContext_Settings_FromConfig(const ConfigurationJSON *);
