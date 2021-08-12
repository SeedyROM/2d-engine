//
// Created by rombus on 8/12/21.
//

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
} RenderContext;

RenderContext *RenderContext_Create();

void RenderContext_Destroy(RenderContext *);
