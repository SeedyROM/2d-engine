//
// Created by rombus on 8/10/21.
//

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
Resource {
    const char *name;
    uintptr_t data;
    struct Resource *next;
}
Resource;

typedef struct
ResourceManager {
    const char *error;
    Resource *root;
}
ResourceManager;

ResourceManager *ResourceManager_Create();
void ResourceManager_Destroy(ResourceManager *);


const char *
ResourceManager_GetError(ResourceManager *);

bool
ResourceManager_Add(ResourceManager *, const char *, uintptr_t);

uintptr_t
ResourceManager_Get(ResourceManager *, const char *);
